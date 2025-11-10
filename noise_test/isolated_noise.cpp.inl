// Define guards to prevent including original headers
#define LL_LLVIEWERPRECOMPILEDHEADERS_H
#define LL_LLRAND_H
#define LLMATH_H

// Include the MSVC LCG compatibility payload first
#include "mocks/msvc-lcg.inl"

// Include the original noise files
#include "../indra/newview/noise.h"
#include "../indra/newview/noise.cpp"
