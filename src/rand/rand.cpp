/* rand.cpp - C wrapper for libstdc++ <random>
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
#include "rand.h"
#include <random>

std::ranlux24 _rl_gen;

std::uniform_int_distribution<char> _distro(0, 8);



void R_ranlux_seed(const unsigned int s) {
	_rl_gen.seed(s);
}
unsigned int R_ranlux_get() {
	return _rl_gen();
}



#ifdef USE_KNUTH_B
std::knuth_b _kb_gen;
void R_knuth_b_seed(const unsigned int s) {
	_kb_gen.seed(s);
}
unsigned int R_knuth_b_get() {
	return _kb_gen();
}
#endif



#ifdef USE_MERSENNE
std::mt19937 _mt_gen;
void R_mt_seed(const unsigned int s) {
	_mt_gen.seed(s);
}
unsigned int R_mt_get() {
	return _mt_gen();
}
#endif



void R_distro_set(const char start, const char end) {
	_distro = std::uniform_int_distribution<char>(start, end);
}

char R_distro_get() {
	return _distro(_rl_gen);
}



