# Roadmap

- [x] v0.1 Repo, BOM, phantom, simulated firmware
- [ ] v0.2 Integrate ad5940lib; match phantom model within 2% / 2 deg
- [ ] v0.3 Add TMP117, MAX30102, LIS2DW12 drivers; timestamp-align all streams
- [ ] v0.4 PPG-gated ensemble averaging of impedance (pulse-synchronous delta-Z)
- [ ] v0.5 Flex PCB electrode array (KiCad) and wearable enclosure
- [ ] v1.0 Data collection protocol with reference measurements (hematocrit / viscometer), ethics approval

## Validation plan (summary)
Collect paired data (patch features vs. reference). Control for skin temperature, hydration,
electrode placement and motion. Evaluate with cross-validated regression and report limits of agreement.
Raw skin/tissue impedance dominates the signal; whether a rheology component can be isolated is an open research question.
