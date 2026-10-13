#pragma once
// 1 = simulated impedance (RC phantom model), 0 = real AD5941 (needs driver, see impedance.cpp)
#define USE_SIM 1

#define PIN_SPI_SCK   4
#define PIN_SPI_MISO  5
#define PIN_SPI_MOSI  6
#define PIN_SPI_CS    7
#define PIN_AFE_RST   3
#define PIN_AFE_INT   2
#define PIN_I2C_SDA   8
#define PIN_I2C_SCL   9

#define SWEEP_POINTS   16
#define SWEEP_F_START  1000.0f    // Hz
#define SWEEP_F_STOP   100000.0f  // Hz

#define TMP117_ADDR    0x48

#define BLE_DEVICE_NAME  "TIRP-Patch"
#define BLE_SERVICE_UUID "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define BLE_CHAR_UUID    "6e400003-b5a3-f393-e0a9-e50e24dcca9e"
