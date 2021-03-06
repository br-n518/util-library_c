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
#include "hash.h"

/**
 * @brief Convert a string to an integer hash value.
 * @param p String to hash.
 * @param p_len Length of string @p p.
 * @returns A hash value representing string @p p.
 * 
 */
int _hash(const char *p, const int p_len) {
	assert( p != 0 );
	assert( p_len > 0 );
	// very import that ret is unsigned.
	// Scenario: Signed char becomes negative, cast to signed int.
	// Accessing that is definitely a seg fault. Mystery solved.
	unsigned char ret = 0;
	for (int i = 0; i < p_len; i++) {
		ret = (ret << 1) ^ (unsigned char) p[i];
	}
	return (int) (ret % HASH_TABLE_SIZE);
}





/**
 * @brief Set data for hash table.
 * @param ht Hash table pointer.
 * @param key String used to create hash.
 * @param key_len Length of string @p key.
 * @param v Variable pointer to assign.
 * @see free_hash_table
 * @see ht_get
 * 
 * Set a void pointer as the data stored in hash table.
 * Hash table won't make a copy, but @b free_hash_table will free the pointer data.
 * This can be problematic if a deep delete is needed. (Delete dependencies before free_hash_table call)
 */
void ht_set(hash_table *ht, const char *key, const int key_len, void *data) {
	assert( ht );
	assert( key );
	assert( key_len > 0 );
	assert( key_len < HASH_KEY_BUFFER_SIZE );
	
	struct hash_table_entry *hte = & (ht->entries[_hash(key, key_len)]);

	if ( hte->key[0] == '\0' ) {
		strncpy(hte->key, key, key_len);
		hte->key[key_len] = '\0';
		hte->data = data;
	} else {
		do {
			if ( strncmp(hte->key, key, key_len) == 0 ) {
				// set value
				hte->data = data;
				break;
			// key string didn't match, and no more next nodes
			} else if (hte->next == 0) {
				// create node
				hte->next = _MALLOC(sizeof(struct hash_table_entry));
				// switch to created node
				hte = hte->next;
				hte->next = 0;
				// copy key and set value
				strncpy(hte->key, key, key_len);
				hte->key[key_len] = '\0';
				hte->data = data;
				//hte->key_len = key_len;
				break;
			}
			hte = hte->next;
		} while (hte != 0);
	}
}




/**
 * @brief Get the data stored in table by given key.
 * @param ht hash_table object to search.
 * @param key Key string to search for.
 * @param key_len Length of key string @p key.
 * @returns The data pointer found, or null if no match.
 * @see ht_set
 * 
 */
void* ht_get(hash_table *ht, const char *key, const int key_len) {
	assert( ht );
	assert( key );
	assert( key_len > 0 );
	assert( key_len < HASH_KEY_BUFFER_SIZE );
	
	struct hash_table_entry *hte = & ht->entries[_hash(key, key_len)];
	
	if ( hte->key[0] != '\0' ) {
		do {
			if ( strncmp(hte->key, key, key_len) == 0 ) {
				return hte->data;
			}
		
			hte = hte->next;
		} while (hte != 0);
	}
	
	return 0;
}




/**
 * @brief Get a hash_table_entry by index. Useful for iterating all contents.
 * @param ht hash_table object to search.
 * @param idx Index of hash_table_entry to get.
 * @returns Returns a pointer to internal hash_table_entry.
 * @see ht_get
 * 
 */
struct hash_table_entry* ht_get_idx( hash_table *ht, const int idx ) {
	assert( idx >= 0 );
	assert( idx < HASH_TABLE_SIZE );
	
	return &(ht->entries[idx]);
}




/**
 * @brief Free hash table node found by @p key. Return value found.
 * @param ht Hash table pointer.
 * @param key String used to create hash.
 * @param key_len Length of string @p key.
 * @returns Returns the data value stored, or 0 if not found.
 * @see ht_remove
 * 
 */
void* ht_unset( hash_table *ht, const char *key, const int key_len ) {
	assert( ht );
	assert( key );
	assert( key_len > 0 );
	assert( key_len < HASH_KEY_BUFFER_SIZE );
	
	struct hash_table_entry *hte = & ht->entries[_hash(key, key_len)];
	struct hash_table_entry *prev = 0;
	// search entry node list
	do {
		// if keys match
		if ( hte->key[0] != '\0' && strncmp(hte->key, key, key_len) == 0 ) {
			void *data = hte->data;
			// if first item in list:
			if ( prev == 0 ) {
				// if last item in list
				if (hte->next == 0) {
					hte->key[0] = '\0';
					hte->data = 0;
				// if first in list and not alone
				} else {
					// overwrite data pointer (data was already freed above)
					hte->data = hte->next->data;
					// update key
					int len = strlen( hte->next->key );
					strncpy(hte->key, hte->next->key, len);
					hte->key[len] = '\0';
					// temp, prev is NULL
					prev = hte->next;
					// overwrite next pointer
					hte->next = hte->next->next;
					// Data pointer is moved, next pointer remapped, it's ok to delete the node
					// free copied node
					_FREE(prev);
				}
			// if not first item in list
			} else {
				// connect prev and next nodes (next could be null, that's ok)
				prev->next = hte->next;
				// free this node
				_FREE(hte);
			}
			return data;
		}
		prev = hte;
		hte = hte->next;
	} while (hte != 0);
	return 0;
}





/**
 * @brief Return value based on if hash_table contains a matching key. Case-sensitive comparison.
 * @return Returns 1 if hash_table contains data at @p key. Returns zero otherwise.
 * 
 */
int ht_has( hash_table *ht, const char *key, const int key_len ) {
	assert( ht != 0 );
	assert( key != 0 );
	assert( key_len > 0 );
	assert( key_len < HASH_KEY_BUFFER_SIZE );
	
	struct hash_table_entry *hte = & ht->entries[_hash(key, key_len)];
	if (hte->key[0] != '\0') {
		do {
			if ( strncmp(hte->key, key, key_len) == 0 ) return 1;
			hte = hte->next;
		} while (hte != 0);
	}
	return 0;
}




/**
 * @brief Initialize a hash_table.
 * @param ht hash_table object to initialize.
 * @see ht_clear
 * @see ht_clear_free
 * 
 */
void ht_init( hash_table *ht ) {
	assert( ht );
	
	memset( ht, 0, sizeof(hash_table) );
}



/**
 * @brief Clear a hash_table and free memory.
 * @param ht hash_table object to clear.
 * @note Data pointers aren't free. For that use ht_clear_free.
 * @see ht_clear_free
 * 
 * 
 */
void ht_clear( hash_table *ht ) {
	assert( ht );
	
	struct hash_table_entry *hte, *prev;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hte = & ht->entries[i];
		if ( hte->key[0] != '\0' ) {
			
			hte->key[0] = '\0';
			hte->data = 0;
			
			hte = hte->next;
			while ( hte ) {
				prev = hte;
				hte = hte->next;
				_FREE(prev);
			}
		}
	}
}

/**
 * @brief Clear a hash_table and free all data.
 * @param ht hash_table to clear.
 * @param free_func Function pointer to be used on stored data pointers.
 * @see ht_clear
 * 
 */
void ht_clear_free( hash_table *ht, void (*free_func) (void*) ) {
	assert( ht );
	assert( free_func );
	
	struct hash_table_entry *hte, *prev;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hte = & (ht->entries[i]);
		if ( hte->key[0] != '\0' ) {
			
			// first node
			hte->key[0] = '\0';
			if ( hte->data )
			{
				free_func(hte->data);
			}
			hte->data = 0;
			
			hte = hte->next;
			// tail
			while ( hte ) {
				if ( hte-> data )
				{
					free_func( hte->data );
				}
				prev = hte;
				hte = hte->next;
				_FREE(prev);
			}
		}
	}
}


/**
 * @brief Remove a value from hash_table.
 * @param ht hash_table to search.
 * @param data Data pointer to search for.
 * @returns Returns the data pointer removed, or zero if no match.
 * @see ht_unset
 * 
 */
void* ht_remove( hash_table *ht, void *data ) {
	assert( ht );
	assert( data );
	
	struct hash_table_entry *hte, *prev;
	for (int i = 0; i < HASH_TABLE_SIZE; i++) {
		hte = & (ht->entries[i]);
		if ( hte->key[0] != '\0' ) {
			prev = 0;
			while ( hte != 0 ) {
				if ( hte->data == data ) {
					// if first node in list
					if ( prev == 0 ) {
						if ( hte->next ) {
							hte->data = hte->next->data;
							int len = strlen(hte->next->key);
							strncpy( hte->key, hte->next->key, len);
							hte->key[len] = '\0';
							prev = hte->next;
							hte->next = hte->next->next;
							_FREE( prev );
						// no previous node, no next node. Single node to remove.
						} else {
							hte->key[0] = '\0';
							hte->data = 0;
							hte->next = 0;
						}
					// if not first node in list
					} else {
						prev->next = hte->next;
						_FREE( hte );
					}
					return data;
				}
				hte = hte->next;
				prev = hte;
			} //end while
		}
	} //end for
	return 0;
}

