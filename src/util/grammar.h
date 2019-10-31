/* grammar.h
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
#ifndef EVOLVE_GRAMMAR_H_
#define EVOLVE_GRAMMAR_H_

#include "node.h"
#include "vector_str.h"
#include <assert.h>
#include <string.h>

#ifdef GODOT
#	include "../gdnative/godot_sub_native.h"
#	define _MALLOC api->godot_alloc
#	define _FREE api->godot_free
#else
#	include <stdlib.h>
#	define _MALLOC malloc
#	define _FREE free
#endif

#define GRAMMAR_STRING_BUFFER_SIZE 64

typedef struct rule_t {
	char from[GRAMMAR_STRING_BUFFER_SIZE], to[GRAMMAR_STRING_BUFFER_SIZE];
} rule_t;



#ifdef __cplusplus
extern "C" {
#endif

void push_grammar_rule( node_t **list, const char *from, const char *to );

void destroy_grammar( node_t *list );


char* create_grammar_str( const char *init_str, node_t *rules, const int iterations );



#ifdef __cplusplus
}
#endif

#endif

