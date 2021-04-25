#pragma once

#include "quantum.h"

#define LAYOUT_ortho_1x16( \
    k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, K0G \
  ) { \
    { k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E, k0F, K0G } \
}

#define LAYOUT LAYOUT_ortho_1x16 