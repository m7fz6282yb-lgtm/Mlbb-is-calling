#include <Arduino.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "config.h"
#include "impedance.h"

static BLECharacteristic* pChar = nullptr;
static bool connected = false;

class ServerCb : public BLEServerCallbacks {
  void onConnect(BLEServer*) override { connected = true; }
  void onDisconnect(BLEServer* s) override { connected = false; s->startAdvertising(); }
};

float read_tmp117() {
  Wire.beginTransmission(TMP117_ADDR);
  Wire.write(0x00);
  if (Wire.endTransmission(false) != 0) return NAN;
  if (Wire.requestFrom((int)TMP117_ADDR, 2) != 2) return NAN;
  int16_t raw = (Wire.read() << 8) | Wire.read();
  return raw * 0.0078125f;  // 7.8125 mC/LSB
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  if (!impedance_begin()) Serial.println("# AFE init failed");

  BLEDevice::init(BLE_DEVICE_NAME);
  BLEServer* srv = BLEDevice::createServer();
  srv->setCallbacks(new ServerCb());
  BLEService* svc = srv->createService(BLE_SERVICE_UUID);
  pChar = svc->createCharacteristic(BLE_CHAR_UUID, BLECharacteristic::PROPERTY_NOTIFY);
  pChar->addDescriptor(new BLE2902());
  svc->start();
  srv->getAdvertising()->addServiceUUID(BLE_SERVICE_UUID);
  srv->getAdvertising()->start();

  Serial.println("# t_ms,temp_C,freq_Hz,re_ohm,im_ohm");
}

void loop() {
  static ZPoint sw[SWEEP_POINTS];
  if (impedance_sweep(sw, SWEEP_POINTS)) {
    float t = read_tmp117();
    uint32_t ms = millis();
    for (int i = 0; i < SWEEP_POINTS; i++) {
      Serial.printf("%lu,%.2f,%.1f,%.3f,%.3f\n", (unsigned long)ms, t, sw[i].freq_hz, sw[i].re_ohm, sw[i].im_ohm);
      if (connected) {
        char buf[64];
        int len = snprintf(buf, sizeof(buf), "%lu,%.2f,%.0f,%.2f,%.2f", (unsigned long)ms, t, sw[i].freq_hz, sw[i].re_ohm, sw[i].im_ohm);
        pChar->setValue((uint8_t*)buf, len);
        pChar->notify();
        delay(10);
      }
    }
  }
  delay(1000);
}
