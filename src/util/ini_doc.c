/* ini_doc.c
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
#include "ini_doc.h"

/**
 * @brief Allocate and initialize a new INI document.
 * @returns Allocated pointer.
 * 
 * 
 */
void ini_doc_init( struct ini_doc *doc )
{
	ht_init( &(doc->sections) );
	ht_init( &(doc->globals) );
}

/**
 * @brief Deallocate an ini_doc document.
 * @param doc The document to destroy.
 * 
 * 
 */
void ini_doc_destroy( struct ini_doc *doc )
{
	assert( doc );
	
	//
	// struct ini_doc:
	//   - sections_table, entries, keys_table, entries, char_ptr
	//   - globals_table, entries, char_ptr
	//
	// entries = struct hash_table_entry [HASH_TABLE_SIZE]:
	//   - key	= char [HASH_KEY_BUFFER_SIZE]
	//   - data	= void*
	//   - next	= struct hash_table_entry*
	//
	
	// clear globals
	ht_clear_free( &(doc->globals), _FREE );
	
	// clear sections
	struct hash_table_entry *temp_entry;
	
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		// loop sections
		temp_entry = ht_get_idx( &(doc->sections), i );
		
		while (temp_entry)
		{
			// loop section node chain
			if (temp_entry->data)
			{
				ht_clear_free( (hash_table*) temp_entry->data, _FREE );
				_FREE( temp_entry->data );
				temp_entry->data = 0;
			}
			
			//hash_table_entry *prev_entry = temp_entry
			temp_entry = temp_entry->next;
			//_FREE( prev_entry );
		}
	}
	
	// clear doc
	ht_clear_free( &(doc->sections), _FREE );
}





/**
 * @brief Set the value for a key under a given section name.
 * @param doc ini_doc to modify.
 * @param section Section to store value in.
 * @param key Key name of key-val pair.
 * @param value Value string of key-val pair.
 * 
 * 
 */
void ini_doc_set( struct ini_doc *doc, const char *section, const char *key, const char *value)
{
	assert( doc ); assert( section ); assert( key ); assert( value );
	
	const int sect_len = strlen(section);
	hash_table *sect = ini_doc_get_section( doc, section, sect_len );
	if ( ! sect )
	{
		sect = _MALLOC( sizeof(hash_table) );
		ht_init( sect );
		ht_set( &(doc->sections), section, sect_len, sect );
	}
	int val_len = strlen(value) + 1;
	char *duple = _MALLOC(val_len);
	strncpy( duple, value, val_len );
	
	int key_len = strlen(key);
	char *prev_val = ht_get(sect, key, key_len);
	if ( prev_val )
	{
		_FREE( prev_val );
	}
	ht_set( sect, key, key_len, duple );
}


/**
 * @brief Set the value for a key under the global section.
 * @param doc ini_doc to modify.
 * @param key Key of key-val pair.
 * @param value Value of key-val pair.
 * 
 * 
 */
void ini_doc_set_global( struct ini_doc *doc, const char *key, const char *value )
{
	assert( doc ); assert( key ); assert( value );
	
	int val_len = strlen(value) + 1;
	char *duple = _MALLOC( val_len );
	strncpy( duple, value, val_len );
	
	int key_len = strlen(key);
	char *prev_val = ht_get(&(doc->globals), key, key_len);
	if ( prev_val )
	{
		_FREE( prev_val );
	}
	ht_set( &(doc->globals), key, key_len, duple );
}


/**
 * @brief Get a key-val's value from given section name.
 * @param doc ini_doc to search.
 * @param section Section to look under.
 * @param key Key to find.
 * @returns Returns the char string at given section and key, or null for not found.
 * 
 * 
 */
char* ini_doc_get( struct ini_doc *doc, const char *section, const char *key )
{
	assert( doc ); assert( section ); assert( key );
	
	hash_table *sect = ini_doc_get_section( doc, section, strlen(section) );
	if ( sect )
	{
		return (char*) ht_get( sect, key, strlen(key) );
	}
	return 0;
}


/**
 * @brief Get a key-val's value from the global section.
 * @param doc ini_doc to search.
 * @param key Key to find.
 * @returns Returns the char string value of given key, or zero for not found.
 * 
 * 
 */
char* ini_doc_get_global( struct ini_doc *doc, const char *key )
{
	assert( doc ); assert( key );
	
	return (char*) ht_get( &(doc->globals), key, strlen(key) );
}


/**
 * @brief Get the hash_table representing section name.
 * @param doc ini_doc to search.
 * @param section Section name of hash_table to get.
 * @returns Returns a hash_table pointer to internal section table.
 * 
 * 
 */
hash_table* ini_doc_get_section( struct ini_doc *doc, const char *section, const int sect_len )
{
	assert( doc ); assert( section );
	
	return (hash_table*) ht_get( &(doc->sections), section, sect_len );
}



void ini_doc_write_keyvals( hash_table *table, FILE *file )
{
	assert( table ); assert( file );
	
	struct hash_table_entry *hte;
	
	for ( int i = 0; i < HASH_TABLE_SIZE; i++ )
	{
		hte = ht_get_idx( table, i );
		if ( hte->key[0] )
		{
			fprintf( file, "%s=%s\n", hte->key, (char*) hte->data );
			hte = hte->next;
			while ( hte )
			{
				fprintf( file, "%s=%s\n", hte->key, (char*) hte->data );
				hte = hte->next;
			}
		}
	}
}




void ini_doc_write_section( struct ini_doc *doc, const char *section, FILE *file )
{
	assert( doc ); assert( section ); assert( file );
	
	fprintf(file, "[%s]\n", section);
	
	ini_doc_write_keyvals( ini_doc_get_section( doc, section, strlen(section) ), file );
}



void ini_doc_write_globals( struct ini_doc *doc, FILE *file )
{
	assert( doc ); assert( file );
	
	ini_doc_write_keyvals( &(doc->globals), file );
}



/**
 * @brief Save an ini_doc as a file.
 * @param doc ini_doc to save.
 * @param filename Filename of destination file.
 * @see ini_doc_load
 * @see ini_doc_parse
 * 
 */
void ini_doc_save( struct ini_doc *doc, const char *filename )
{
	assert( doc ); assert( filename );
	
	FILE *file = fopen(filename, "w");
	if ( file )
	{
		// write global section
		ini_doc_write_globals( doc, file );
		
		// loop through sections
		struct hash_table_entry *temp_entry;
		for ( int i = 0; i < HASH_TABLE_SIZE; i++ )
		{
			// get section
			temp_entry = ht_get_idx( &(doc->sections), i );
			if ( temp_entry->key[0] != '\0' )
			{
				ini_doc_write_section( doc, temp_entry->key, file );
				
				temp_entry = temp_entry->next;
				while (temp_entry)
				{
					ini_doc_write_section( doc, temp_entry->key, file );
					temp_entry = temp_entry->next;
				}
			}
		}
		
		fclose( file );
		
	}
	else
	{
		printf( "ini_doc_save: Could not open file for saving." );
	}
}


















enum doc_parse_state
{
	LINE_START = 1,
	LINE_SECTION,
	LINE_KEYVAL_LEFT,
	LINE_KEYVAL_RIGHT
};

// ignore leading keyval pairs. Require a section header.
// Pound sign of course is comment (ignore leading space, handle comments at end of line, but no preserve for any comments)
/**
 * @brief Parse a character string as INI file data.
 * @param doc ini_doc object to receive data.
 * @param data Char string to parse sections and key-val pairs from.
 * @see ini_doc_load
 * @note Comments begin with the pound sign (#). Comments can be on own line or following a section/key-val.
 * @note Comments are stripped and ignored.
 * 
 * 
 */
void ini_doc_parse( struct ini_doc *doc, const char *data )
{
	assert( doc );
	assert( data );
	
	const int DATA_LEN = strlen( data );
	
	strbuff sb;
	sb_init( &sb );
	
	// data offset index, and parsing state enum
	int offset_idx = 0;
	enum doc_parse_state state = 0;
	
	// section
	hash_table *section_ptr = &(doc->globals);
	
	// line buffer (for sb)
	char *curr_line;
	int curr_line_len;
	
	// loop data per line
	while ( offset_idx < DATA_LEN && offset_idx >= 0 )
	{
		// get next line
		offset_idx = sb_get_next_line( &sb, data, DATA_LEN, offset_idx );
		
		// get length of line
		curr_line_len = sb_len( &sb );
		
		if ( curr_line_len > 0 )
		{
			// convert line to c string
			curr_line = sb_cstr( &sb );
			// reset sb, keeping allocated blocks for reuse.
			sb_reset( &sb );
			
			char *temp_c, *key = 0;
			int temp_len, key_len = 0;
			unsigned char kv_value_started = 0, curr_ch;
			
			// PROCESS LINE
			for (int i = 0; i < curr_line_len; i++)
			{
				// current character
				curr_ch = curr_line[i];
				
				// if state is zero
				if ( state == 0 )
				{
					// if current character isn't whitespace
					if ( ! isspace(curr_ch) )
					{
						// begin line processing
						state = LINE_START;
					}
				}
				
				// state machine
				switch (state)
				{
					
					case LINE_START:
						switch (curr_ch)
						{
							case '[':
								state = LINE_SECTION;
								break;
							case '=':
							case '#':
								//discard line
								goto CLABEL_line_finish;
							default:
								// not space and not special char, so keyval
								state = LINE_KEYVAL_LEFT;
								sb_putc( &sb, curr_ch );
						}
						break;
						
					case LINE_SECTION:
						switch (curr_ch)
						{
							case ']':
								// get section name
								temp_c = sb_cstr( &sb );
								temp_len = sb_len( &sb );
								sb_reset( &sb );
								
								// get section pointer
								section_ptr = ht_get( &(doc->sections), temp_c, temp_len );
								// if not created
								if ( ! section_ptr )
								{
									// create section
									section_ptr = _MALLOC( sizeof(hash_table) );
									ht_init( section_ptr );
									// store section_ptr hash_table inside base hash_table
									// temp_c holds the section name string
									ht_set( &(doc->sections), temp_c, temp_len, section_ptr );
								}
								// free name array
								_FREE( temp_c );
								//temp_c = 0;
								state = 0;
								// break FOR loop
								goto CLABEL_line_finish;
							case ' ':
							case '\t':
								break; //skip spaces and tabs
							default:
								// store regular characters
								sb_putc( &sb, curr_ch );
						}
						break;
						
					case LINE_KEYVAL_LEFT:
						switch (curr_ch)
						{
							case '=':
								// change state
								state = LINE_KEYVAL_RIGHT;
								kv_value_started = 0; //skip leading space flag
								
								key = sb_cstr( &sb );
								key_len = sb_len(&sb);
								sb_reset( &sb );
								break;
							case ' ':
							case '\t':
								// ignore all spaces in key...
								break;
							default:
								// regular character
								sb_putc( &sb, curr_ch );
						}
						break;
						
					case LINE_KEYVAL_RIGHT:
						switch (curr_ch)
						{
							case ' ':
							case '\t':
								// ignore leading whitespace, include the rest
								if ( kv_value_started ) // value string started
								{
									// string was started, include the space
									sb_putc( &sb, curr_ch );
								}
								// else do nothing
								break;
							
							default:
								// regular character
								kv_value_started = 1;
								sb_putc( &sb, curr_ch );
						}
						break;
						
					default:
						break;
				} //end switch
				
			} //end for
			
			// label to break for loop
			CLABEL_line_finish:
			
			// at this point the line has ended, so check state for final actions
			if ( state == LINE_KEYVAL_RIGHT ) // if the line ended with keyval
			{
				sb_strip_trailing( &sb );
				
				char *prev_val = ht_get( section_ptr, key, key_len );
				if ( prev_val ) _FREE( prev_val );
				// set value
				// allocate c string for data
				if ( sb_len(&sb) > 0 )
				{
					ht_set( section_ptr, key, key_len, sb_cstr( &sb ) );
				}
				else
				{
					ht_set( section_ptr, key, key_len, 0 );
				}
				
				_FREE( key );
				key = 0;
				key_len = 0;
				
				sb_reset( &sb );
			}
			else if (state == LINE_KEYVAL_LEFT)
			{
				key = sb_cstr( &sb );
				
				ht_set( section_ptr, key, sb_len( &sb ), 0 );
				
				_FREE( key );
				key = 0;
				sb_reset( &sb );
			}
			
			state = 0;
			
			_FREE( curr_line );
		}
		else
		{
			sb_reset( &sb );
		}
	} //end while
	// clean up memory
	sb_clear( &sb );
}

/**
 * @brief Open and parse an INI file.
 * @param dest ini_doc to use for data storage.
 * @param filename Name of file to open.
 * @returns Returns zero if file not found. Returns 1 otherwise.
 * @see ini_doc_parse
 * @see ini_doc_save
 * 
 */
char ini_doc_load( struct ini_doc *dest, const char *filename )
{
	assert( dest );
	assert( filename );
	
	FILE *file = fopen(filename, "r");
	if ( file )
	{
		strbuff sb;
		sb_init( &sb );
		
		while ( ! feof(file) )
		{
			int c = fgetc(file);
			if ( c > 0 )
			{
				sb_putc( &sb, c );
			}
			else if ( c <= 0 )
			{
				break;
			}
		}
		fclose( file );
		
		char *cstr = sb_cstr(&sb);
		sb_clear( &sb );
		
		ini_doc_parse( dest, cstr );
		_FREE( cstr );
		
		return 1;
	}
	return 0;
}


