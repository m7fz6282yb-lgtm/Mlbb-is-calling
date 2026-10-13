# TIRP: Transcutaneous Impedance Rheology Patch

Open prototype of a wrist-worn patch that measures **tetrapolar bioimpedance (multi-frequency)**
and logs it together with skin temperature, PPG and motion, as a research platform for exploring
whether blood-rheology-related signals (e.g. viscosity / RBC aggregation) can be estimated non-invasively.

> **Status: v0.1 concept prototype. Research tool only, NOT a medical device.**
> Never use for diagnosis or treatment. Read [`docs/safety.md`](docs/safety.md) before connecting to a person.

## Repo layout

| Path | Content |
|---|---|
| `hardware/BOM.csv` | Bill of materials |
| `hardware/block_diagram.md` | System block diagram (Mermaid) |
| `hardware/pinmap.md` | MCU ↔ AFE/sensor wiring for the first breadboard build |
| `hardware/electrode_layout.svg` | 4-electrode flex-PCB layout |
| `hardware/phantom/` | Bench phantom (RC Cole model) for testing without a person |
| `firmware/` | PlatformIO project (ESP32-C3, BLE). Runs in **simulation mode** with no hardware |
| `tools/cole_model.py` | Python: compute/plot expected phantom sweep |
| `docs/` | Safety notes, roadmap, validation plan |

## Quick start

```bash
# 1) Expected phantom curve
pip install numpy matplotlib
python tools/cole_model.py

# 2) Firmware (simulated sweep over serial + BLE)
cd firmware && pio run -t upload && pio device monitor
```

Set `USE_SIM` to `0` in `firmware/src/config.h` once the AD5941 driver is integrated
(see TODO in `firmware/src/impedance.cpp`).

## Concept

```
4 electrodes (I+ V+ V- I-) -> AD5941 AFE -> MCU -> BLE -> phone
                              TMP117, MAX30102, LIS2DW12 as context sensors
```

Pulse-synchronous impedance change (ΔZ from PPG-gated averaging) is the candidate signal
of arterial blood volume/composition. Skin and tissue dominate the raw value, so calibration
against a reference (hematocrit, viscometer) is mandatory. See `docs/roadmap.md`.

## License
Code: MIT. Hardware files: CERN-OHL-P-2.0 (suggested; change as you see fit).
