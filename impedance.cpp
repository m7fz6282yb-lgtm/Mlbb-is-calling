#include <Arduino.h>
#include <math.h>
#include "config.h"
#include "impedance.h"

#if USE_SIM
// Simulated phantom: Rs + Rp / (1 + jwRpC), Rs=100, Rp=500, C=100nF
static const float RS = 100.0f, RP = 500.0f, CC = 100e-9f;

bool impedance_begin() { return true; }

bool impedance_sweep(ZPoint* out, int n) {
  for (int i = 0; i < n; i++) {
    float f = SWEEP_F_START * powf(SWEEP_F_STOP / SWEEP_F_START, (float)i / (n - 1));
    float w = 2.0f * (float)M_PI * f;
    float x = w * RP * CC;
    float d = 1.0f + x * x;
    float re = RS + RP / d;
    float im = -RP * x / d;
    re += ((float)random(-100, 100)) / 100.0f;  // small noise
    im += ((float)random(-100, 100)) / 100.0f;
    out[i] = {f, re, im};
  }
  return true;
}

#else
// TODO: integrate Analog Devices ad5940lib (https://github.com/analogdevicesinc/ad5940lib)
//  - Port its MCU-specific SPI/GPIO layer (AD5940Port.c) to ESP32 Arduino SPI
//  - Base the sweep on the AD5940_BIOZ example (4-wire, frequency sweep)
//  - Use minimum excitation amplitude, DC-blocking caps in place, RCAL = 1k
//  - Convert DFT real/imag into ohms using the RCAL reference
bool impedance_begin() { return false; }
bool impedance_sweep(ZPoint*, int) { return false; }
#endif
