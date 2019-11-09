/*
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
#ifndef EVOLVE_GRAMMAR_H_
#define EVOLVE_GRAMMAR_H_

#include "node.h"
#include "vector_str.h"
#include <assert.h>
#include <string.h>

#include "../alloc.h"

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

