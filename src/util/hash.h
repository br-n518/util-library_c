/* hash.h
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
#ifndef HASH_UTIL_H_
#define HASH_UTIL_H_

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#ifndef HASH_KEY_BUFFER_SIZE
#	define HASH_KEY_BUFFER_SIZE 64
#endif

#ifndef HASH_TABLE_SIZE
#	define HASH_TABLE_SIZE 61
#endif

/**
 * @brief Single entry in a hash table, holding key and data.
 */
struct hash_table_entry {
	char key[HASH_KEY_BUFFER_SIZE];
	void *data;
	struct hash_table_entry *next;
};

/**
 * @brief Hash table for storing @b variant objects by string key.
 */
typedef struct hash_table {
	struct hash_table_entry entries[HASH_TABLE_SIZE];
} hash_table;

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


void ht_set( hash_table*, const char*, const int key_len, void* );
void* ht_get( hash_table*, const char*, const int );
struct hash_table_entry* ht_get_idx( hash_table *ht, const int idx );

void* ht_unset( hash_table*, const char*, const int );

int ht_has( hash_table*, const char*, const int );

void ht_init( hash_table *ht );

// will zero data pointers. If they're not stored elsewhere, use ht_clear_free
void ht_clear( hash_table* );
void ht_clear_free( hash_table*, void (*free_func) (void*) );

void* ht_remove( hash_table*, void* );

#ifdef __cplusplus
}
#endif

#endif
