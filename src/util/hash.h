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
#ifndef HASH_UTIL_H_
#define HASH_UTIL_H_

#include <assert.h>
#include <string.h>

#include "../alloc.h"

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

void ht_set( hash_table*, const char *key, const int key_len, void *data );
void* ht_get( hash_table*, const char *key, const int key_len );
struct hash_table_entry* ht_get_idx( hash_table *ht, const int idx );

void* ht_unset( hash_table*, const char *key, const int key_len );

int ht_has( hash_table*, const char *key, const int key_len );

void ht_init( hash_table *ht );

// will zero data pointers. If they're not stored elsewhere, use ht_clear_free
void ht_clear( hash_table* );
void ht_clear_free( hash_table*, void (*free_func) (void*) );

void* ht_remove( hash_table*, void *data );

#ifdef __cplusplus
}
#endif



#endif
