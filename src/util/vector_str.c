/* vector_str.c
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
#include "vector_str.h"


/**
 * @brief Initialize a vector_str.
 * @param s The vector_str to initialize.
 * 
 * 
 */
void vs_init( vector_str *s)
{
	assert( s );
	
	s->head = 0;
}

vs_node* vs_node_create( const char c )
{
	vs_node *ret = _MALLOC( sizeof( *ret ) );
	ret->data = c;
	ret->next = 0;
	return ret;
}

void vs_node_free( vs_node *n )
{
	if ( n )
	{
		if ( n->next )
		{
			vs_node_free( n->next );
		}
		_FREE( n );
	}
}

/**
 * @brief Destroy a vector_str object, freeing internal memory.
 * @param s The vector_str to free.
 * 
 * 
 */
void vs_destroy( vector_str *s )
{
	assert( s );
	
	vs_node_free( s->head );
	s->head = 0;
}

/**
 * @brief Set the contents of a vector_str.
 * @param s The vector_str to modify.
 * @param src The new string for the vector_str.
 * 
 * 
 */
void vs_set( vector_str *s, const char *src )
{
	assert( s );
	vs_node_free( s->head );
	s->head = 0;
	int len = strlen( src );
	if ( len > 0 )
	{
		s->head = vs_node_create( src[0] );
		vs_node *curr = s->head;
		int i = 0;
		while ( ++i < len )
		{
			curr->next = vs_node_create( src[i] );
			curr = curr->next;
		}
	}
}

/**
 * @brief Append a string to a vector_str.
 * @param s The vector_str to modify.
 * @param src The string to append to end of vector_str @p s.
 * 
 * 
 */
void vs_append( vector_str *s, const char *src )
{
	assert( s );
	if ( s->head )
	{
		vs_node *curr = s->head;
		while ( curr->next )
			curr = curr->next;
		int len = strlen(src);
		for ( int i = 0; i < len; i++ )
		{
			curr->next = vs_node_create( src[i] );
			curr = curr->next;
		}
	}
	else
	{
		vs_set( s, src );
	}
}

/**
 * @brief Insert a string into a vector_str.
 * @param s The vector_str to modify.
 * @param src The string to insert.
 * @param index Index for where to insert string @p src.
 * 
 * 
 */
void vs_insert( vector_str *s, const char *src, const int index )
{
	assert( s );
	vs_node *a = s->head;
	
	if ( index > 0 )
	{
		int i = 1;
	
		while ( i < index )
		{
			if ( a->next )
			{
				i++;
				a = a->next;
			}
			else
			{
				break;
			}
		}
		if ( i == index )
		{
			vs_node *b = a->next;
			int si = 0;
			while ( src[si] )
			{
				a->next = vs_node_create( src[si] );
				a = a->next;
				si++;
			}
			a->next = b;
		}
	}
	else
	{
		s->head = vs_node_create( src[0] );
		vs_node *b = a;
		a = s->head;
		int si = 1;
		while ( src[si] )
		{
			a->next = vs_node_create( src[si] );
			a = a->next;
			si++;
		}
		a->next = b;
	}
}


/**
 * @brief Get a character at given index.
 * @param s The vector_str to modify.
 * @param index Index to check.
 * @returns Returns null char if index out of bounds.
 * 
 * 
 */
char vs_char_at( vector_str *s, const int index )
{
	assert( s );
	vs_node *curr = s->head;
	int i = 0;
	while ( i < index )
	{
		if ( curr->next )
		{
			curr = curr->next;
			i++;
		}
		else
		{
			// no next, index out of bounds
			return '\0';
		}
	}
	return curr->data;
}


/**
 * @brief Get the index of first matching char found.
 * @param s The vector_str to modify.
 * @param c The char to search for.
 * @returns Returns the index of found character, or -1 for no match.
 * 
 * 
 */
int vs_index_of_c( vector_str *s, const char c )
{
	assert( s );
	
	if ( s->head )
	{
		vs_node *curr = s->head;
		int i = 0;
		while ( curr->data != c )
		{
			if ( curr->next )
			{
				curr = curr->next;
				i++;
			}
			else
			{
				return -1;
			}
		}
		return i;
	}
	return -1;
}

/**
 * @brief Get the index of first matching string found.
 * @param s The vector_str to modify.
 * @param c The character string to search for.
 * @returns Returns the index found, or -1 for no match.
 * 
 * 
 */
int vs_index_of_s( vector_str *s, const char *c )
{
	assert( s );
	assert( c );
	
	if ( s->head )
	{
		vs_node *curr = s->head, *temp = 0;
		int i = 0, ci = 0;
		const int clen = strlen(c);
		while ( curr )
		{
			if ( curr->data == c[ci] )
			{
				ci++;
				temp = curr->next;
				
				while ( ci < clen && temp )
				{
					if ( temp->data == c[ci] )
					{
						ci++;
						temp = temp->next;
					}
					else
					{
						ci = 0;
						break;
					}
				}
				if ( ci == clen )
					return i;
			}
			i++;
			curr = curr->next;
		}
	}
	return -1;
}



/**
 * @brief Get the index of first matching char found, beginning search from given index.
 * @param s The vector_str to modify.
 * @param c The char to search for.
 * @param index Index to start search from.
 * @returns Returns the index found, or -1 for no match.
 * 
 * 
 */
int vs_index_of_c_idx( vector_str *s, const char c, const int index )
{
	assert( s );
	if ( s->head ) {
		vs_node *curr = s->head;
		int i = 0;
		while ( i < index )
		{
			if ( !(curr = curr->next) )
				return -1;
			i++;
		}
		while ( curr && curr->data != c )
		{
			curr = curr->next;
			i++;
		}
		if ( curr && curr->data == c )
			return i;
	}
	return -1;
}


/**
 * @brief Get the index of first matching string found, beginning search from given index.
 * @param s The vector_str to search.
 * @param c The char string to search for.
 * @param index Index to start search from.
 * @returns Returns the index found, or -1 for no match.
 * 
 * 
 */
int vs_index_of_s_idx( vector_str *s, const char *c, const int index )
{
	assert( s );
	assert( c );
	
	if ( s->head )
	{
		vs_node *curr = s->head, *temp = 0;
		int i = 0, ci = 0;
		const int clen = strlen(c);
		// get node at index
		while ( i < index && curr )
		{
			curr = curr->next;
			i++;
		}
		// loop nodes (if curr is null, then index out of bounds)
		while ( curr )
		{
			// if chars match
			if ( curr->data == c[ci] )
			{
				ci++;
				temp = curr->next;
				
				while ( ci < clen && temp )
				{
					if ( temp->data == c[ci] )
					{
						ci++;
						temp = temp->next;
					}
					else
					{
						ci = 0;
						break;
					}
				}
				if ( ci == clen )
				{
					return i;
				}
			}
			// get next node to search from
			i++;
			curr = curr->next;
		}
	}
	return -1;
}



/**
 * @brief Get the length of a vector_str.
 * @param s The vector_str to process.
 * @returns Returns the length of the vector_str.
 * 
 * 
 */
int vs_length( vector_str *s )
{
	assert( s );
	vs_node *curr = s->head;
	int i = 0;
	while ( curr )
	{
		i++;
		curr = curr->next;
	}
	return i;
}

/**
 * @brief Get a vector_str as a C-style character string.
 * @param s The vector_str to copy.
 * @returns A null-terminated character string. Use _FREE when done.
 * @see vs_gets
 * 
 */
char* vs_cstr( vector_str *s )
{
	assert( s );
	char *ret = _MALLOC( vs_length( s ) + 1 );
	int i = 0;
	vs_node *curr = s->head;
	while ( curr )
	{
		ret[i] = curr->data;
		curr = curr->next;
		i++;
	}
	ret[i] = '\0';
	return ret;
}



/**
 * @brief Copy the contents of a vector_str to a char buffer.
 * @param s The vector_str to copy data from.
 * @param dest The char buffer to write to.
 * @param max_chars Max length of the char buffer @p dest.
 * @note If @p max_chars not reached, append a null char to buffer.
 * @see vs_cstr
 * 
 */
void vs_gets( vector_str *s, char *dest, const int max_chars )
{
	assert( s );
	assert( dest );
	assert( max_chars > 0 );
	
	vs_node *curr = s->head;
	
	int i = 0;
	for ( ; i < max_chars && curr; i++ )
	{
		dest[i] = curr->data;
		curr = curr->next;
	}
	
	if ( i < max_chars)
	{
		dest[i] = '\0';
	}
}


/**
 * @brief 
 * @param s The vector_str to modify.
 * @param from 
 * @param to 
 * 
 * 
 */
void vs_replace( vector_str *s, const char *from, const char *to )
{
	assert( s );
	const int flen = strlen( from );
	vs_node *curr = s->head, *prev = 0;
	// search for 'from'
	while ( curr )
	{
		if ( curr->data == from[0] )
		{
			vs_node *check = curr;
			int i = 0;
			while ( ++i < flen )
			{
				check = check->next;
				if ( !( check && check->data == from[i] ) )
				{
					i = -1;
					break;
				}
			}
			// if all 'from' chars matched
			if ( i == flen )
			{
				// store tail
				vs_node *tail = check->next;
				// allow free, without freeing tail.
				check->next = 0;
				// done with check pointer
				check = 0;
				// if curr is not head node
				if ( prev )
				{
					// clear 'from' string
					vs_node_free( curr );
					curr = 0;
					// set null for vs_append call
					prev->next = 0;
					// append replacement text 'to'
					vs_append( s, to );
				}
				else
				{
					// curr is head node
					// just set whole string
					vs_set( s, to );
				}
				// apply tail
				if ( s->head )
				{
					check = s->head;
					while ( check->next )
					{
						check = check->next;
					}
					check->next = tail;
				}
				else
				{
					s->head = tail;
				}
				// done processing
				return;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}



/**
 * @brief Replace part of a vector_str, beginning search from given index.
 * @param s The vector_str to modify.
 * @param from String to search for and replace (if found).
 * @param to Replacement string.
 * @param index Index to start search from.
 * 
 * 
 */
void vs_replace_idx( vector_str *s, const char *from, const char *to, const int index )
{
	assert( s );
	assert( from );
	assert( to );
	
	vs_node *curr = s->head, *prev = 0, *check;
	
	
	const int flen = strlen( from );
	
	// check index, head pointer, and length of from-string
	if ( index < 0 || !curr || flen <= 0 )
	{
		return;
	}
	
	// get character at start index
	int i = 0;
	while ( i < index && curr )
	{
		prev = curr;
		curr = curr->next;
		i++;
	}
	
	if ( !curr )
	{
		// index out of bounds
		return;
	}
	
	// search for 'from'
	while ( curr )
	{
		// found matching first char
		if ( curr->data == from[0] )
		{
			check = curr;
			// recycle i var
			i = 0;
			// get end of from string
			while ( ++i < flen )
			{
				check = check->next;
				if ( !( check && check->data == from[i] ) )
				{
					i = -1;
					break;
				}
			}
			// if all 'from' chars matched
			if ( i == flen )
			{
				// 'curr' holds starting char (of 'from')
				// 'check' holds tail char (of 'from')
				
				// store tail (may be null)
				vs_node *tail = check->next;
				// allow free chain without freeing tail.
				check->next = 0;
				// done with check pointer
				check = 0;
				// if curr is not head node (then prev is set)
				if ( prev )
				{
					// clear 'from' string
					vs_node_free( curr );
					curr = 0;
					// set null for vs_append call
					prev->next = 0;
					// append replacement text 'to'
					vs_append( s, to );
				}
				else
				{
					// curr is head node
					// just set 'to' string to be whole vector_str
					vs_set( s, to );
				}
				// apply tail
				if ( s->head )
				{
					check = s->head;
					// get tail of added 'to' string
					while ( check->next )
						check = check->next;
					// apply tail
					check->next = tail;
				}
				else
				{
					// no head ('to' string is empty, whole vector_str matched 'from' string)
					s->head = tail;
				}
				// done processing
				return;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}



/**
 * @brief Check if a vector_str matches a char string. Returns non-zero for a match.
 * @param s The vector_str to test.
 * @param cstr The char string to test.
 * @returns Zero for no match, non-zero for matching string.
 * 
 * 
 */
int vs_test( vector_str *s, const char *cstr )
{
	assert( s );
	assert( cstr );
	
	char *p = vs_cstr( s );
	int ret = ( strcmp( p, cstr ) == 0 );
	_FREE( p );
	
	return ret;
	
}



