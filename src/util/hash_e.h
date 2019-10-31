/* hash_e.h
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
#ifndef EHASH_UTIL_H_
#define EHASH_UTIL_H_

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

#ifndef EHASH_KEY_BUFFER_SIZE
#	define EHASH_KEY_BUFFER_SIZE 64
#endif

#ifndef EHASH_TABLE_SIZE
#	define EHASH_TABLE_SIZE 101
#endif

/**
 * @brief Single entry in a hash table, holding key and data.
 */
struct hash_table_e_entry {
	char key[EHASH_KEY_BUFFER_SIZE];
	void *data;
	struct hash_table_e_entry *next;
};

/**
 * @brief Hash table for storing @b variant objects by string key.
 */
typedef struct hash_table_e {
	struct hash_table_e_entry *entries[EHASH_TABLE_SIZE];
} hash_table_e;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Generate a byte-size hash from a string key.
 * 
 * @param key String used to create hash.
 * @param key_len Length of string @p key.
 */
int _hash(const char *key, const int key_len);


void eht_set( hash_table_e*, const char*, const int key_len, void* );
void* eht_get( hash_table_e*, const char*, const int );
struct hash_table_e_entry* eht_get_idx( hash_table_e *ht, const int idx );

void* eht_unset( hash_table_e*, const char*, const int );

int eht_has( hash_table_e*, const char*, const int );

void eht_init( hash_table_e *ht );

// will zero data pointers. If they're not stored elsewhere, use eht_clear_free
void eht_clear( hash_table_e* );
void eht_clear_free( hash_table_e*, void (*free_func) (void*) );

void* eht_remove( hash_table_e*, void* );

#ifdef __cplusplus
}
#endif

#endif
