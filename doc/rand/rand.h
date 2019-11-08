/* rand.h - C wrapper for libstdc++ <random>
 *
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org>
 */
#ifndef CXX_RAND_4_C_H
#define CXX_RAND_4_C_H

// To use the optional RNGs place the define in this header (i.e. uncomment the following)
//#define USE_KNUTH_B
//#define USE_MERSENNE

#ifdef __cplusplus
extern "C" {
#endif

/// R_ranlux_* enabled by default (define USE_KNUTH_B and USE_MERSENNE for the others)
// global variables are hidden in rand.cpp (C can't use/have them, only the functions defined here)

/**
 * \brief Seed the Ranlux24 generator. (ranlux24_base with discard_block)
 * Balanced generator.
 */
void R_ranlux_seed(const unsigned int);
unsigned int R_ranlux_get();


#ifdef USE_KNUTH_B
/**
 * \brief Seed the Knuth-B generator. (minstd_rand0 with shuffle_order)
 * Fast generator.
 */
void R_knuth_b_seed(const unsigned int);
unsigned int R_knuth_b_get();
#endif


#ifdef USE_MERSENNE
/**
 * \brief Seed the mt19937 generator.
 * Complex generator.
 */
void R_mt_seed(const unsigned int);
unsigned int R_mt_get();
#endif


/**
 * \brief Configure the uniform_int_distribution <char>
 */
void R_distro_set(const char start, const char end);
/**
 * \brief Use the uniform_int_distribution <char> on R_ranlux_get()
 */
char R_distro_get();



#ifdef __cplusplus
}
#endif

#endif
