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
#include "strbuff.h"




/**
 * @brief Reset buffer for re-use. Existing memory will be left allocated for later.
 * @param sb strbuff object to operate on.
 * @note Use sb_clear to free the memory too.
 * @see sb_clear
 */
void sb_reset( strbuff *sb )
{
	assert( sb );
	
	sb->curr = & sb->head;
	sb->put_pos = 0;
}

/**
 * @brief Initialize strbuff. This will lose any existing daisy chain memory.
 * @param sb strbuff object to operate on.
 * @note To reset a strbuff, use sb_reset. Only use sb_init for a new strbuff.
 * @see sb_reset
 * @see sb_clear
 */
void sb_init( strbuff *sb )
{
	assert( sb );
	
	sb->head.next = 0;
	sb_reset( sb );
}




void sbpart_free( struct strbuff_part *sbp )
{
	assert( sbp );
	
	if ( sbp->next ) sbpart_free(sbp->next);
	_FREE( sbp );
}


/**
 * @brief Clear the strbuff's data and free the pointer itself.
 * @param sb strbuff object to operate on.
 * @see sb_clear
 * @see sb_reset
 * 
 */
void sb_free( strbuff *sb )
{
	assert( sb );
	
	if ( sb->head.next ) sbpart_free( sb->head.next );
	_FREE( sb );
}

/**
 * @brief Clear the strbuff's memory blocks and reinitialize.
 * @param sb strbuff object to operate on.
 * @see sb_reset
 * @see sb_free
 * 
 */
void sb_clear( strbuff *sb )
{
	assert( sb );
	
	if ( sb->head.next ) sbpart_free( sb->head.next );
	sb_init( sb );
}




void sb_add_part( strbuff *sb )
{
	assert( sb );
	
	if ( ! sb->curr->next )
	{
		sb->curr->next = _MALLOC( sizeof(struct strbuff_part) );
		sb->curr->next->next = 0;
	}
}



void sb_check( strbuff *sb )
{
	while ( sb->put_pos >= STRBUFF_PARTITION_SIZE )
	{
		if ( sb->curr->next == 0 )
		{
			sb_add_part( sb );
		}
		sb->curr = sb->curr->next;
		sb->put_pos -= STRBUFF_PARTITION_SIZE;
	}
}



/**
 * @brief Get length of @struct strbuff.
 * @param sb strbuff object to operate on.
 * @returns String length.
 * 
 * 
 */
int sb_len( strbuff *sb )
{
	assert( sb );
	assert( sb->curr );
	
	int ret = 0;
	struct strbuff_part * curr = & sb->head;
	while ( curr != sb->curr )
	{
		ret = ret + STRBUFF_PARTITION_SIZE;
		curr = curr->next;
	}
	return ret + sb->put_pos;
}



/**
 * @brief Set a character value by index.
 * @param sb strbuff object to operate on.
 * @param index Target index to find.
 * @param ch New value for char at given index (if found).
 * @warning see todo
 * @todo Need to more clearly define: What happens with index OOB?
 */
void sb_setc( strbuff *sb, const int index, const char ch )
{
	assert( sb );
	assert( index >= 0 );
	assert( ch != 0 );
	
	const int x = (index % STRBUFF_PARTITION_SIZE);
	int part_whole = index - x;
	int n = 0;
	while ( part_whole >= STRBUFF_PARTITION_SIZE )
	{
		part_whole = part_whole - STRBUFF_PARTITION_SIZE;
		n++;
	}
	
	struct strbuff_part * part = & sb->head;
	
	for (; n > 0; n--)
	{
		if (part->next == 0)
		{
			sb_add_part(sb);
			sb->curr = sb->curr->next;
			sb->put_pos = 0;
		}
		part = part->next;
	}
	
	if ( part == sb->curr && x >= sb->put_pos )
	{
		sb->put_pos = x + 1;
		sb_check( sb );
	}
	part->data[x] = ch;
}


/**
 * @brief Append a character to the end of the @struct strbuff.
 * @param sb strbuff object to operate on.
 * @param ch Character to add.
 * 
 * 
 */
void sb_putc( strbuff *sb, const char ch )
{
	assert( sb );
	
	sb->curr->data[sb->put_pos] = ch;
	sb->put_pos++;
	sb_check( sb );
}


/**
 * @brief Get a character by index.
 * @param sb strbuff object to operate on.
 * @param index String index.
 * @returns Returns the character at the index, or returns 0 for out of bounds index.
 * 
 * 
 */
char sb_getc( strbuff *sb, const int index )
{
	assert( sb );
	assert( index >= 0 );
	
	const int x = (index % STRBUFF_PARTITION_SIZE);
	int part_whole = index - x;
	int n = 0;
	while ( part_whole >= STRBUFF_PARTITION_SIZE )
	{
		part_whole = part_whole - STRBUFF_PARTITION_SIZE;
		n++;
	}
	struct strbuff_part * part = & sb->head;
	for (; n > 0; n--)
	{
		if (part->next != 0) part = part->next;
		else return '\0';
	}
	return part->data[x];
}



/**
 * @brief Copy the contents of a strbuff to a char buffer.
 * @param sb strbuff object to copy from.
 * @param dest Char buffer to write to.
 * @param max_chars Max length of buffer @p dest.
 * @returns Returns the length of string written to buffer.
 * @see sb_cstr
 * 
 */
int sb_gets( strbuff *sb, char *dest, const int max_chars )
{
	assert( sb );
	assert( dest );
	
	int i = 0, x;
	struct strbuff_part *curr = & sb->head;
	
	while ( curr != sb->curr && i < max_chars )
	{
		for ( x = 0; x < STRBUFF_PARTITION_SIZE && i < max_chars; x++ )
		{
			dest[i++] = curr->data[x];
		}
		curr = curr->next;
	}
	if ( curr == sb->curr )
	{
		for ( x = 0; x < sb->put_pos && i < max_chars; x++ )
		{
			dest[i++] = curr->data[x];
		}
	}
	if ( i < max_chars )
	{
		dest[i] = '\0';
	}
	return i;
}


/**
 * @brief Append a string to the strbuff @p sb .
 * @param sb strbuff object to operate on.
 * @param src String to copy.
 * @param src_len Length of copy string.
 * 
 * 
 */
void sb_puts( strbuff *sb, const char *src, const int src_len )
{
	assert( sb );
	assert( src );
	
	for ( int i = 0; i < src_len; i++ ) {
		sb_putc( sb, src[i] );
	}
}

/**
 * @brief Concatenate @p cat to end of @p sb.
 * @param sb strbuff object to operate on.
 * @param cat strbuff to append.
 * 
 * 
 */
void sb_cat( strbuff *sb, strbuff *cat )
{
	assert( sb);
	assert( cat );
	
	struct strbuff_part *row = & cat->head;
	int x;
	do {
		for ( x = 0; x < STRBUFF_PARTITION_SIZE; x++ )
		{
			sb_putc( sb, row->data[x] );
		}
		row = row->next;
	} while ( row != cat->curr );
	for ( x = 0; x < cat->put_pos; x++ )
	{
		sb_putc( sb, row->data[x] );
	}
}


/**
 * @brief Get a strbuff as a C-style character string.
 * @param sb strbuff object to operate on.
 * @returns A null-terminated character string. Use _FREE when done.
 * @see sb_gets
 * 
 */
char* sb_cstr( strbuff *sb )
{
	assert( sb );
	
	const int len = sb_len(sb);
	
	char *ret = 0;
	if ( len > 0 )
	{
		// create string
		ret = _MALLOC( len + 1 );
		sb_gets( sb, ret, len );
		ret[len] = '\0';
	}
	
	return ret;
}


/**
 * @brief Strip trailing space from the end of @p sb.
 * @param sb strbuff object to operate on.
 * 
 * 
 */
void sb_strip_trailing( strbuff *sb )
{
	assert( sb );
	
	const int len = sb_len( sb );
	int i = len - 1;
	
	if ( len > 0 && isspace( sb_getc(sb, len - 1) ) )
	{
		while ( i >= 0 )
		{
			if ( ! isspace( sb_getc(sb, i) ) )
			{
				// i is now the right-most non-space character ( ! isspace() )
				int k = 0;
				struct strbuff_part *sbp = &(sb->head);
				
				// use end of string for reference
				i++; // looking for put_pos, not last character
				
				// get nearest strbuff_part pointer
				while ( k + STRBUFF_PARTITION_SIZE <= i )
				{
					sbp = sbp->next;
					k += STRBUFF_PARTITION_SIZE;
				}
				
				// apply result
				sb->curr = sbp;
				sb->put_pos = i - k;
				
				// all done
				return;
			}
			i--;
		}
		
		sb_reset( sb );
	}
}



/**
 * @brief Search a string (@p data) from starting index (@p from_idx) until a newline is found.
 * @param dest_buffer strbuff object to operate on.
 * @param data Data string to search through.
 * @param data_len Length of data string (@p data)
 * @param from_idx Index to begin search from.
 * @returns Returns the index of the first character following the newline character.
 * 			If no newline is found then return negative one (-1).
 * 
 * 
 */
int sb_get_next_line( strbuff *dest_buffer, const char *data, const int data_len, const int from_idx )
{
	assert( dest_buffer ); assert( data ); assert( from_idx >= 0 );
	
	int i = from_idx;
	
	for ( ; i < data_len; i++ )
	{
		switch (data[i])
		{
			case '\0':
			case '\f':
			case '\v':
				break;
			case '\r':
				// CARRIAGE RETURN
				if ( i+1 < data_len )
				{
					// CR AND LF (windows)
					if ( data[i+1] == '\n')
					{
						if (i+2 < data_len) return i+2; // windows
					}
					// NO LINE FEED
					else return i+1; // mac
				}
				break;
			case '\n':
				// LINE FEED
				return i+1; // linux
			default:
				sb_putc( dest_buffer, data[i] );
		}
	}
	return -1;
}









