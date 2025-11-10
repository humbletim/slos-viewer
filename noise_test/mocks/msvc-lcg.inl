#pragma once

#ifdef USE_MSVC_COMPAT
// Vendored MSVC LCG
static unsigned long int s_compat_next = 1;
inline int msvc_compat_rand(void)
{
    s_compat_next = s_compat_next * 214013L + 2531011L;
    return (unsigned int)((s_compat_next >> 16) & 0x7fff);
}
inline void msvc_compat_srand(unsigned int seed)
{
    s_compat_next = seed;
}

// The magic override:
#define rand  msvc_compat_rand
#define srand msvc_compat_srand
#endif
