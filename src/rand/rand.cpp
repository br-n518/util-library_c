/* rand.cpp - C wrapper for libstdc++ <random>
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



