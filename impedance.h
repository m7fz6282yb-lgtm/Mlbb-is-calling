#pragma once
#include <stdint.h>

struct ZPoint {
  float freq_hz;
  float re_ohm;
  float im_ohm;
};

bool impedance_begin();
// Fills out[0..n-1] with a log-spaced sweep. Returns true on success.
bool impedance_sweep(ZPoint* out, int n);
