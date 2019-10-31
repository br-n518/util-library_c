/* ini_doc.h
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
#ifndef INI_DOC_H
#define INI_DOC_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>

#ifdef GODOT
#	include "../gdnative/godot_sub_native.h"
#	define _MALLOC api->godot_alloc
#	define _FREE api->godot_free
#else
#	include <stdlib.h>
#	define _MALLOC malloc
#	define _FREE free
#endif

#include "strbuff.h"
#include "hash.h"

// sections are saved as hash table entries
// each section is itself a hash table
// each section table holds the key and void* value.
// void* data is to be a char* null terminated
// API needs a function to free all the memory.

struct ini_doc {
	hash_table sections, globals;
};



#ifdef __cplusplus
extern "C" {
#endif

void ini_doc_init( struct ini_doc *doc );
void ini_doc_destroy( struct ini_doc* );

void ini_doc_set( struct ini_doc *doc, const char *section, const char *key, const char *value);
void ini_doc_set_global( struct ini_doc *doc, const char *key, const char *value );

char* ini_doc_get( struct ini_doc *doc, const char *section, const char *key ); //
char* ini_doc_get_global( struct ini_doc *doc, const char *key ); //

hash_table* ini_doc_get_section( struct ini_doc *doc, const char *section, const int sect_len );

void ini_doc_save( struct ini_doc *doc, const char *filename );

void ini_doc_parse( struct ini_doc *doc, const char *data );
char ini_doc_load( struct ini_doc *dest, const char *filename );

#ifdef __cplusplus
}
#endif

#endif

