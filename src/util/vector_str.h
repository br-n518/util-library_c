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
#ifndef VECSTR_H_
#define VECSTR_H_

#include <assert.h>
#include <string.h>

#include "../alloc.h"

typedef struct vs_node {
	char data;
	struct vs_node *next;
} vs_node;


/**
 * @brief Store a string as single-character linked-list nodes. For mutability.
 * 
 * 
 */
typedef struct vector_str {
	vs_node *head; /**< Head pointer for character linked list. */
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
void vs_gets( vector_str *s, char *dest, const int max_chars );

void vs_replace( vector_str *s, const char *from, const char *to );
void vs_replace_idx( vector_str *s, const char *from, const char *to, const int index );

// slow, used for testing
int vs_test( vector_str *s, const char *cstr );


#ifdef __cplusplus
}
#endif

#endif
