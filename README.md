# Bench phantom

Single-dispersion RC model (no skin required):

```
V+ o--[Rs 100R]--+--[Rp 500R]--+--o V-
                 |             |
                 +--[C 100nF]--+
```

Z(w) = Rs + Rp / (1 + j*w*Rp*C)

- |Z| at low f ~ 600 ohm, at high f ~ 100 ohm
- Corner frequency fc = 1/(2*pi*Rp*C) ~ 3.18 kHz
- Use 1% resistors and a C0G capacitor. Run `python tools/cole_model.py` for the expected curve.

Pass criterion for v0.1: measured |Z| within 2% and phase within 2 degrees of the model, 1 kHz to 100 kHz.
