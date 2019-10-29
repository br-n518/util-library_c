/* vector_str.h
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
#ifndef VECSTR_H_
#define VECSTR_H_

#include <string.h>
#include <stdlib.h>

typedef struct vs_node {
	char data;
	struct vs_node *next;
} vs_node;


typedef struct vector_str {
	vs_node *head;
} vector_str;

#ifdef __cplusplus
extern "C" {
#endif

void vs_init( vector_str *s);
void vs_destroy( vector_str *s );

void vs_set( vector_str *s, const char *src );
void vs_append( vector_str *s, const char *src );
void vs_insert( vector_str *s, const char *src, const int index );

char vs_char_at( vector_str *s, const int index );

int vs_index_of_c( vector_str *s, const char c );
int vs_index_of_s( vector_str *s, const char *c );

int vs_index_of_c_idx( vector_str *s, const char c, const int index );
int vs_index_of_s_idx( vector_str *s, const char *c, const int index );

int vs_length( vector_str *s );

char* vs_cstr( vector_str *s );

void vs_replace( vector_str *s, const char *from, const char *to );
void vs_replace_idx( vector_str *s, const char *from, const char *to, const int index );

// slow, used for testing
int vs_test( vector_str *s, const char *cstr );


#ifdef __cplusplus
}
#endif

#endif
