#!/usr/bin/env python3
"""Expected impedance sweep for the bench phantom, plus a generic Cole model."""
import numpy as np

RS, RP, C = 100.0, 500.0, 100e-9


def phantom_z(f):
    w = 2 * np.pi * np.asarray(f, dtype=float)
    return RS + RP / (1 + 1j * w * RP * C)


def cole_z(f, r0=600.0, rinf=100.0, tau=50e-6, alpha=0.85):
    w = 2 * np.pi * np.asarray(f, dtype=float)
    return rinf + (r0 - rinf) / (1 + (1j * w * tau) ** alpha)


if __name__ == "__main__":
    f = np.logspace(3, 5, 16)
    z = phantom_z(f)
    print("f_Hz, |Z|_ohm, phase_deg")
    for fi, zi in zip(f, z):
        print(f"{fi:9.1f}, {abs(zi):8.2f}, {np.degrees(np.angle(zi)):7.2f}")
    try:
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
        fig, ax = plt.subplots(2, 1, sharex=True)
        ax[0].semilogx(f, abs(z), "o-"); ax[0].set_ylabel("|Z| (ohm)")
        ax[1].semilogx(f, np.degrees(np.angle(z)), "o-"); ax[1].set_ylabel("phase (deg)")
        ax[1].set_xlabel("Frequency (Hz)")
        plt.tight_layout(); plt.savefig("phantom_expected.png", dpi=150)
        print("saved phantom_expected.png")
    except ImportError:
        pass
