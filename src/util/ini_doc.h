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
#ifndef INI_DOC_H
#define INI_DOC_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "../alloc.h"

#include "strbuff.h"
#include "hash.h"

// sections are saved as hash table entries
// each section is itself a hash table
// each section table holds the key and void* value.
// void* data is to be a char* null terminated

/**
 * @brief INI style document reader/writer struct.
 * 
 * 
 */
struct ini_doc {
	hash_table sections, globals; /**< Table of INI sections. */ /**< INI key-val pairs at head of file, before any section headers. */
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

char* ini_doc_to_string( struct ini_doc *doc );

#ifdef __cplusplus
}
#endif

#endif

