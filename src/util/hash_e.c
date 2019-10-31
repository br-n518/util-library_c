/* hash_e.c
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
#include "hash_e.h"

int _hash_e(const char *p, const int p_len) {
	assert( p );
	assert( p_len > 0 );
	// very import that ret is unsigned.
	// Scenario: Signed char becomes negative, cast to signed int.
	// Accessing that is definitely a seg fault. Mystery solved.
	unsigned char ret = 0;
	for (int i = 0; i < p_len; i++) {
		ret = (ret << 1) ^ (unsigned char) p[i];
	}
	return (int) (ret % EHASH_TABLE_SIZE);
}





/**
 * @brief Set data for hash table.
 * 
 * Set a void pointer as the data stored in hash table.
 * @param ht Hash table pointer.
 * @param key String used to create hash.
 * @param key_len Length of string @p key.
 * @param v Variable pointer to assign.
 * @see eht_clear(), eht_clear_free()
 */
void eht_set(hash_table_e *ht, const char *key, const int key_len, void *data)
{
	assert( ht );
	assert( key );
	assert( key_len > 0 );
	assert( key_len < EHASH_KEY_BUFFER_SIZE );
	
	const int hash_key = _hash_e(key, key_len);
	
	struct hash_table_e_entry *hte = ht->entries[hash_key];
	
	if ( ! hte )
	{
		hte = _MALLOC( sizeof( struct hash_table_e_entry ) );
		memset( hte, 0, sizeof( struct hash_table_e_entry ));
		ht->entries[hash_key] = hte;
	}
	
	if ( hte->key[0] == '\0' )
	{
		strncpy(hte->key, key, key_len);
		hte->key[key_len] = '\0';
		hte->data = data;
	}
	else
	{
		do
		{
			if ( strncmp(hte->key, key, key_len) == 0 )
			{
				// set value
				hte->data = data;
				break;
			// key string didn't match, and no more next nodes
			}
			else if (hte->next == 0)
			{
				// create node
				hte->next = _MALLOC(sizeof(struct hash_table_e_entry));
				// switch to created node
				hte = hte->next;
				hte->next = 0;
				// copy key and set value
				strncpy(hte->key, key, key_len);
				hte->key[key_len] = '\0';
				hte->data = data;
				break;
			}
			hte = hte->next;
		} while (hte != 0);
	}
}




void* eht_get( hash_table_e *ht, const char *key, const int key_len )
{
	assert( ht );
	assert( key );
	assert( key_len > 0 );
	assert( key_len < EHASH_KEY_BUFFER_SIZE );
	
	struct hash_table_e_entry *hte = ht->entries[_hash_e(key, key_len)];
	
	if ( hte && hte->key[0] != '\0' )
	{
		do
		{
			if ( strncmp(hte->key, key, key_len) == 0 )
			{
				return hte->data;
			}
		
			hte = hte->next;
		} while (hte);
	}
	
	return 0;
}




struct hash_table_e_entry* eht_get_idx( hash_table_e *ht, const int idx ) {
	assert( idx >= 0 );
	assert( idx < EHASH_TABLE_SIZE );
	
	return ht->entries[idx];
}




/**
 * @brief Free hash table node found by @p key. Return value found.
 * @param ht Hash table pointer.
 * @param key String used to create hash.
 * @param key_len Length of string @p key.
 * @return data value stored, or 0 if not found.
 */
void* eht_unset( hash_table_e *ht, const char *key, const int key_len )
{
	assert( ht );
	assert( key );
	assert( key_len > 0 );
	assert( key_len < EHASH_KEY_BUFFER_SIZE );
	
	
	const int hash_key = _hash_e(key, key_len);
	struct hash_table_e_entry *hte = ht->entries[hash_key];
	struct hash_table_e_entry *prev = 0;
	
	// search entry node list
	while (hte)
	{
		// if key exists and keys match
		if ( hte->key[0] != '\0' && strncmp(hte->key, key, key_len) == 0 )
		{
			void *data = hte->data; //store data pointer
			
			// if in middle or at end of list
			if ( prev )
			{
				prev->next = hte->next;
			}
			// if first in list
			else
			{
				ht->entries[hash_key] = hte->next;
			}
			
			_FREE(hte);
			return data;
		}
		prev = hte;
		hte = hte->next;
	}
	return 0;
}





/**
 * @brief Return value based on if hash_table_e contains a matching key. Case-sensitive comparison.
 * @return 1 if hash_table_e contains data at @p key. 0 otherwise.
 * @see strncmp
 */
int eht_has( hash_table_e *ht, const char *key, const int key_len ) {
	assert( ht );
	assert( key );
	assert( key_len > 0 );
	assert( key_len < EHASH_KEY_BUFFER_SIZE );
	
	struct hash_table_e_entry *hte = ht->entries[_hash_e(key, key_len)];
	if ( hte && hte->key[0] != '\0' )
	{
		do
		{
			if ( strncmp(hte->key, key, key_len) == 0 ) return 1;
			hte = hte->next;
		} while (hte);
	}
	return 0;
}




void eht_init( hash_table_e *ht ) {
	assert( ht );
	
	memset( ht, 0, sizeof(hash_table_e) );
}



void eht_clear( hash_table_e *ht ) {
	assert( ht );
	
	struct hash_table_e_entry *hte, *prev = 0;
	for (int i = 0; i < EHASH_TABLE_SIZE; i++) {
		hte = ht->entries[i];
		while (hte)
		{
			prev = hte;
			hte = hte->next;
			_FREE(prev);
		}
		ht->entries[i] = 0;
	}
}

void eht_clear_free( hash_table_e *ht, void (*free_func) (void*) ) {
	assert( ht );
	assert( free_func );
	
	struct hash_table_e_entry *hte, *prev;
	for (int i = 0; i < EHASH_TABLE_SIZE; i++) {
		hte = ht->entries[i];
		(ht->entries)[i] = 0;
		while (hte)
		{
			free_func( hte->data );
			prev = hte;
			hte = hte->next;
			_FREE(prev);
		}
	}
}


void* eht_remove( hash_table_e *ht, void *value ) {
	assert( ht );
	assert( value );
	
	struct hash_table_e_entry *hte, *prev = 0;
	for (int i = 0; i < EHASH_TABLE_SIZE; i++) {
		hte = ht->entries[i];
		while ( hte )
		{
			if (hte->data == value)
			{
				// remove node
				if (prev)
				{
					prev->next = hte->next;
					_FREE( hte );
				}
				else
				{
					ht->entries[i] = hte->next;
					_FREE( hte );
				}
				
				return value;
			}
			
			prev = hte;
			hte = hte->next;
		}
	} //end for
	return 0;
}

