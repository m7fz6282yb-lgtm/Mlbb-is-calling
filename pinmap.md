# Breadboard pin map (ESP32-C3 DevKit + EVAL-AD5941BATZ)

| Signal | ESP32-C3 GPIO | Target |
|---|---|---|
| SPI SCK | 4 | AD5941 SCLK |
| SPI MISO | 5 | AD5941 MISO |
| SPI MOSI | 6 | AD5941 MOSI |
| SPI CS | 7 | AD5941 CS |
| AFE RESET | 3 | AD5941 RESET |
| AFE INT | 2 | AD5941 GPIO0 (interrupt) |
| I2C SDA | 8 | TMP117 / MAX30102 / LIS2DW12 |
| I2C SCL | 9 | TMP117 / MAX30102 / LIS2DW12 |

Pins are a suggested default. Verify against your exact board revision.

## Electrode connection (AD5941 4-wire)
- I+  -> AFE excitation out (via DC-block + series R)
- V+  -> sense P (via DC-block)
- V-  -> sense N (via DC-block)
- I-  -> AFE current return / TIA input (via DC-block)

Confirm exact AD5941 pin names (AIN/CE0/RE0/SE0/DE0) in the ADI datasheet and the
`AD5940_BIOZ` example before wiring.
