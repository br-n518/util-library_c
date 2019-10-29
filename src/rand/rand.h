/* rand.h - C wrapper for libstdc++ <random>
 *
 * Copyright (c) 2019 br-n518
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
