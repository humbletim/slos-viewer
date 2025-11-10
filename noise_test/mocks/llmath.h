// mocks/llmath.h
#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

// --- Mock LL types ---
typedef float F32;
typedef double F64;
typedef int S32;
typedef unsigned int U32;
typedef unsigned char U8;

// --- Mock LL math functions ---
inline S32 lltrunc(F32 f) { return (S32)f; }
inline S32 llfloor(F32 f) { return (S32)floor(f); }

// --- THE PAYLOAD ---
// (This has been moved to msvc-lcg.inl)
