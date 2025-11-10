## Standalone `noise.h` Test Harness

This directory contains a standalone test harness to prove a cross-platform dissonance bug exists in `noise.cpp` due to differences in `srand()` and `rand()` implementations across standard libraries.

### Key Findings

To the theory of standardizing `noise.h`, several visual inconsistencies in these other areas become fixed too:

1.  **Terrain Composition (`llvlcomposition.cpp`)**:
    *   **CRITICAL**: This file uses `noise2` to generate the actual *geometry heights* for terrain composition (L549: `twiddle = noise2(vec1)*6.5f;`).
    *   If you used the isolated patch *only* for textures, the terrain *shape* might slightly mismatch the terrain *textures* on Linux/Mac, as one would use standard `rand()` and the other would use `msvc_rand()`.
2.  **Avatar "Fidget" (`llvoavatar.cpp`)**:
    *   Uses `noise2` to subtly shift the avatar's torso while standing still to make them look alive (`LLBodyNoiseMotion::onUpdate`). Linux avatars currently "fidget" differently than Windows avatars.
3.  **Avatar Clothes/Wind (`llvoavatar.cpp`, `lldrawpoolavatar.cpp`)**:
    *   Uses `noise1` to ripple clothes in the wind.

Right now, `init()` calls `srand((unsigned int)time(NULL))` at the end. This appears to be a massive side-effect; it means the *first time* any avatar or terrain needs noise, the *entire viewer's* standard RNG gets re-seeded unpredictably.

By vendoring the MSVC LCG into `noise.cpp` and using it *only* for this initialization, we decouple this subsystem from the rest of the viewer's random number generation entirely.

### Compilation Instructions

To compile and run this test, you can use a standard C++ compiler. The `-I` flags are necessary to point to the mock headers.

**Linux/macOS (Clang or GCC):**

```bash
# Compile in "native" mode (uses system rand())
clang++ -Imocks main.cpp -o main_native

# Compile in "fixed" mode (uses MSVC LCG)
clang++ -Imocks -DUSE_MSVC_COMPAT main.cpp -o main_fixed
```

**Windows (MSVC):**

```bash
# Compile in "native" mode (uses system rand())
cl.exe /I "mocks" main.cpp /Femain_native.exe

# Compile in "fixed" mode (uses MSVC LCG)
cl.exe /I "mocks" /DUSE_MSVC_COMPAT main.cpp /Femain_fixed.exe
```
