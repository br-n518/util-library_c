/* xml_doc.c
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
#include "xml_doc.h"



struct xml_docparse_state
{
	struct xml_node *node;
	struct xml_doc *doc;
	char in_quote, strict;
};


char xml_check_xml( const char *buff, const int i )
{
	return
		(buff[i]   =='x' || buff[i]   =='X') &&
		(buff[i+1] =='m' || buff[i+1] =='M') &&
		(buff[i+2] =='l' || buff[i+2] =='L');
}

/** 
 * @brief Check a filename string for valid XML extension at end.
 * @param fname Filename string to check for valid extension.
 * @param len Length of string \p fname.
 * @returns Returns zero for non-xml filename. Returns 1 otherwise.
 * 
 * 
 */
char xml_check_filename( const char *fname, const int len )
{
	assert( fname );
	
	return (
	
			len >= 4 &&
			xml_check_xml(fname, len-3) &&
			fname[len-4] == '.'
			
			) ? 1 : 0;
}



/**
 * @brief Create and initialize a new @struct xml_doc.
 * @returns A new \struct xml_doc as an allocated pointer.
 * @warning Returns an allocated pointer.
 * @see xml_doc_free()
 * 
 * 
 */
struct xml_doc* xml_doc_create()
{
	struct xml_doc *doc = _MALLOC( sizeof(*doc) );
	memset( doc, 0, sizeof(struct xml_doc) );
	strcpy( doc->encoding, "UTF-8" );
	doc->version_major = 1;
	return doc;
}



/**
 * @brief Create and initialize a new @struct xml_node.
 * @param name Tagname of created node.
 * @returns A new xml_node as an allocated pointer.
 * @warning Returns an allocated pointer.
 * @see xml_node_free()
 * 
 * 
 */
struct xml_node* xml_node_create( const char *name )
{
	assert( name );
	assert( strlen(name) < XML_STRING_BUFFER_SIZE );
	
	struct xml_node *node = _MALLOC( sizeof( struct xml_node ) );
	memset( node, 0, sizeof(struct xml_node) );
	strncpy( node->name, name, XML_STRING_BUFFER_SIZE );
	return node;
}



/**
 * @brief Create and initialize a new @struct xml_attribute.
 * @param name Name of attribute.
 * @param value Text value of attribute.
 * @returns A new xml_attribute as an allocated pointer.
 * @warning Returns an allocated pointer.
 * @see xml_attribute_free
 * 
 * 
 */
struct xml_attribute* xml_attribute_create( const char *name, const char *value )
{
	assert( name );
	assert( strlen(name) < XML_STRING_BUFFER_SIZE );
	
	struct xml_attribute *attr = _MALLOC( sizeof( struct xml_attribute ) );
	memset( attr, 0, sizeof( struct xml_attribute ) );
	strncpy( attr->name, name, XML_STRING_BUFFER_SIZE );
	
	xml_text_create( &(attr->text_body), value );
	
	return attr;
}



/**
 * @brief Create and initialize a new @struct xml_text.
 * @param t @struct xml_text object to modify.
 * @param value New value for \struct xml_text.
 * @see xml_text_free
 * 
 * 
 */
void xml_text_create( struct xml_text *t, const char *value )
{
	assert( t );
	assert( value );
	
	if ( t->text )
	{
		xml_text_free( t );
	}
	
	int len = strlen(value);
	if ( len > 0 )
	{
		t->text_len = len;
		t->text = _MALLOC( len + 1 );
		strcpy( t->text, value );
		//t->text[len] = '\0';
	}
}


void xml_text_append ( struct xml_text *t, const char *value )
{
	assert( t );
	assert( value );
	
	const int len = strlen( value );
	if ( len > 0 )
	{
		// check for existing text
		if ( t->text )
		{
			char *ref = t->text;
			
			t->text_len = t->text_len + len;
			t->text = _MALLOC( t->text_len + 1 );
			t->text[0] = '\0';
			
			strcat( t->text, ref );
			strcat( t->text, value );
			
			_FREE( ref );
		}
		else
		{
			xml_text_create( t, value );
		}
	}
}



/**
 * @brief Free internal data of @struct xml_text.
 * @param t Pointer to @struct xml_text for which the internal character string is deallocated.
 * @warning Pointer argument is NOT deallocated. Only the internal character string for @struct xml_text is deallocated.
 * 
 * 
 */
void xml_text_free( struct xml_text *t )
{
	assert( t );
	
	if ( t->text )
	{
		_FREE( t->text );
		memset( t, 0, sizeof( struct xml_text ) );
	}
}



/**
 * @brief Free internal data and free pointer.
 * @param attr 
 * 
 * 
 */
void xml_attribute_free( struct xml_attribute *attr )
{
	assert( attr );
	
	xml_text_free( &(attr->text_body)  );
	_FREE( attr );
}



/**
 * @brief Free internal data and free pointer (free() prototype proxy).
 * @param a Void pointer to be cast as (struct xml_attribute*).
 * @note This function matches the prototype for free(), for use as function pointer.
 * 
 * 
 */
void xml_attribute_proxy_free( void *a )
{
	xml_attribute_free( (struct xml_attribute*) a );
}



/**
 * @brief Free internal data and free pointer.
 * @param node 
 * @param connect_children 
 * 
 * 
 */
void xml_node_free( struct xml_node *node, const char connect_children )
{
	assert( node );
	
	// free text
	xml_text_free( &(node->text_body) );
	
	// free attributes
	ht_clear_free( &(node->attributes), xml_attribute_proxy_free );
	
	// handle child nodes
	if ( connect_children ) {
		// connect children to parent
		struct xml_node *temp;
		node_t *temp_node = node->child_nodes;
		while ( temp_node ) {
			temp = (struct xml_node*) node_pop( &temp_node, temp_node );
			if (temp && temp->parent_node == node) {
				xml_node_add_child( node->parent_node, temp );
			}
			//temp_node = temp_node->next;
		}
	} else {
		// delete all children
		while ( node->child_nodes ) {
			xml_node_free( (struct xml_node*) node_pop( &(node->child_nodes), node->child_nodes ), 0 );
		}
	}
	
	assert( ! node->child_nodes );
	
	_FREE( node );
}



/**
 * @brief Free internal data and free pointer.
 * @param doc
 * 
 * 
 */
void xml_doc_free( struct xml_doc *doc )
{
	assert( doc );
	
	node_t *children = doc->root_node->child_nodes;
	struct xml_node *node;
	while ( children ) {
		node = node_pop( &children, children );
		xml_node_free( node, 0 );
	}
	doc->root_node->child_nodes = 0;
	xml_node_free( doc->root_node, 0 );
}



/**
 * @brief Create a @struct xml_doc object from file.
 * @param fname Filename of XML file to read.
 * @returns @struct xml_doc allocated object.
 * @see xml_doc_save(), xml_doc_parse()
 * 
 * 
 */
struct xml_doc* xml_doc_open( const char *fname, const char strict_formatting_bool )
{
	assert( fname );
	assert( fname[0] != '\0' );
	
	struct xml_doc *ret = 0;
	
	// open file
	FILE *file = fopen( fname, "r" );
	
	// if file is valid
	if ( file ) {
		
		int c = 0;
		strbuff sb;
		sb_init( &sb );
		
		// read file by char
		do {
			c = fgetc(file);
			if ( c == EOF ) break;
			sb_putc( &sb, c );
		} while (1);
		// close opened file
		fclose( file );
		
		// get c-string
		int len = sb_len(&sb);
		char *data = sb_cstr(&sb);
		sb_clear( &sb );
		
		// parse file data
		if ( data )
		{
			ret = xml_doc_parse( data, len, strict_formatting_bool );
			_FREE(data);
		}
		else
		{
			puts("xml_doc_open: Empty file opened.");
		}
	}
	
	return ret;
}




int __str_to_int( const char *s )
{
	int ret = 0;
	
	if ( s )
	{
		int c;
		int i = strlen(s) - 1;
		int k = 0;
		for (; i >= 0 && (c = s[i]); i-- )
		{
			if ( isdigit( c ) )
			{
				if ( c > '0' )
				{
					c = c - '0';
					// adjust tens multiple
					if ( k > 0 )
					{
						for ( int multiple = k; multiple > 0; multiple-- )
						{
							c = c * 10;
						}
					}
					ret = ret + c;
				}
				k++;
			}
		}
	}
	return ret;
}

void xml_docparse_header( struct xml_docparse_state *state, const char *buffer, const int buffer_len )
{
	assert( state );
	assert( state->doc );
	assert( buffer );
	
	if ( buffer_len <= 0 ) return;
	
	strbuff sb;
	sb_init( &sb );
	
	char name_buff[XML_STRING_BUFFER_SIZE];
	name_buff[0] = '\0';
	char value_buff[XML_STRING_BUFFER_SIZE];
	value_buff[0] = '\0';
	
	// parse attributes
	// ignore unrecognized
	int i = 0;
	while ( i < buffer_len )
	{
		if ( state->in_quote )
		{
			char c = buffer[i];
			if ( c == '"' )
			{
				state->in_quote = 0;
				int value_len = sb_gets( &sb, value_buff, XML_STRING_BUFFER_SIZE );
				sb_reset( &sb );
				
				if ( strcmp(name_buff, "version") == 0)
				{
					// parse version string
					char c, *cstr;
					int k = 0;
					while ( (c = value_buff[k++]) && k < XML_STRING_BUFFER_SIZE )
					{
						// collect numerals
						if ( c >= '0' && c <= '9' )
						{
							sb_putc(&sb, c);
						}
						// dot causes process version_major, only two numbers allowed (that is, one dot: 0.0, 1.21, xx.yy )
						else if ( c == '.' )
						{
							cstr = sb_cstr(&sb);
							sb_reset(&sb); //reset for next set of numerals (second and final set)
							state->doc->version_major = __str_to_int(cstr);
							_FREE( cstr );
						}
						else if ( ! state->strict )
						{
							while ( isspace(c) )
							{
								c = value_buff[k++];
							}
						}
						
					} //end while
					cstr = sb_cstr(&sb);
					state->doc->version_minor = __str_to_int(cstr);
					_FREE( cstr );
					sb_reset( &sb );
				}
				else if ( strcmp( name_buff, "encoding") == 0 )
				{
					strncpy( state->doc->encoding, value_buff, value_len );
					state->doc->encoding[value_len] = '\0';
				}
				
				
			}
			else
			{
				sb_putc( &sb, c );
			}
		}
		else
		switch (buffer[i])
		{
			case ' ':
			case '\n':
			case '\r':
			case '\t':
			case '\v':
			case '\f':
			case '?':
				break;
				
			case '=':
				sb_gets( &sb, name_buff, XML_STRING_BUFFER_SIZE );
				sb_reset( &sb );
				break;
				
			case '\\':
				sb_putc( &sb, '\\' );
				i++;
				if ( i < buffer_len )
					sb_putc( &sb, buffer[i] );
				break;
				
			case '"':
				state->in_quote = 1;
				break;
				
			default:
				sb_putc( &sb, buffer[i] );
		}
		i++;
	}
	
	
	sb_clear( &sb );
}




void xml_docparse_attributes( struct xml_docparse_state *state, struct xml_node *node, const char *buffer, const int buffer_len)
{
	assert( state );
	assert( node );
	assert( buffer );
	
	if ( buffer_len <= 0 )
	{
		puts("xml_doc_parse warning: Empty attributes call.");
		return;
	}
	
	state->in_quote = 0;
	
	int i = 0;
	while ( i < buffer_len && isspace(buffer[i]) )
	{
		i++;
	}
	
	strbuff sb;
	sb_init(&sb);
	char name[XML_STRING_BUFFER_SIZE];
	name[0] = '\0';
	char value[XML_LARGE_STRING_BUFFER_SIZE];
	value[0] = '\0';
	
	char found_attribute = 0;
	
	// loop all chars in buffer
	
	for (; i < buffer_len; i++ )
	{
		char c = buffer[i];
		// handle quoted strings
		if ( state->in_quote )
		{
			// escape sequence: backslash causes following character to be included, whatever it is (includes double quote)
			// also, this includes invalid escape sequences. We're not parsing those, just preserving them.
			//  Optionally can print a warning for invalid escape sequences (for convenience to user)
			if ( c == '\\' )
			{
				sb_putc( &sb, c );
				i++;
				if ( i < buffer_len )
				{
					sb_putc( &sb, buffer[i] );
				}
			}
			else if ( c == '"' )
			{
				state->in_quote = 0;
				// set attribute
				if ( found_attribute )
				{
					found_attribute = 0;
					
					sb_gets( &sb, value, XML_LARGE_STRING_BUFFER_SIZE ); // SB_GETS IS here
					sb_reset( &sb );
					xml_node_set_attr( node, name, value );
					name[0] = '\0';
					value[0] = '\0';
					
					if ( state->strict && i+1 < buffer_len )
					{
						if ( ! isspace(buffer[i + 1]) )
						{
							puts("xml_doc_parse warning: Attribute should be followed by a blank space.");
						}
					}
				}
				else
				{
					puts("xml_doc_parse error: Found quoted string without attribute name.");
				}
			}
			else
			{
				sb_putc( &sb, c );
			}
			continue;
		}
		// handle attribute names
		else
		{
			switch ( c )
			{
				case ' ': //space
				case '\t':
				case '\n':
				case '\r':
				case '\f':
				case '\v':
				break;
				case '<':
					// error
					puts("xml_doc_parse error: Expected '>' before '<' in tag line.");
				break;
				case '"':
					// begin quote
					state->in_quote = 1;
				break;
				case '=':
					// record attribute name
					
					// have a rewind index, allow non-quoted attr values
					// by setting rewind to start of latest post-whitespace char
					// finding more space makes rewind movable
					// find equals instead of moving rewind:
					//		applies attribute value
					//		gets following name
					//		starts processing next attribute value (quoted or not)
					// leading space following equals is ignored,
					// and space between final word and next name is ignored/stripped.
					sb_gets( &sb, name, XML_STRING_BUFFER_SIZE );
					sb_reset( &sb );
					found_attribute = 1;
					
				break;
				case '\\':
					puts("xml_doc_parse error: Unexpected '\\' in attribute name.");
					
				break;
				case '/':
					if ( i < buffer_len - 1 )
					{
						puts("xml_doc_parse error: Unexpected '/' among attributes.");
					}
				break;
				default:
					sb_putc( &sb, c );
			}
		}
	}
	
	sb_clear( &sb );
}


void xml_docparse_tag_close( struct xml_docparse_state *state, const char *tag, const int tag_len )
{
	assert( state );
	assert( tag );
	
	if ( tag_len == 0 )
	{
		puts("xml_doc_parse error: Empty closing tag.");
		return;
	}
	
	if ( state->node )
	{
		if ( state->node->parent_node )
		{
			
			if ( state->strict )
			{
				int k = 0;
				// skip blank space
				while ( k < tag_len && isspace(tag[k]) ) k++;
				
				char name_buff[XML_STRING_BUFFER_SIZE], pname_buff[XML_STRING_BUFFER_SIZE];
				
				int x = k;
				int i = 0;
				while ( x < tag_len )
				{
					name_buff[i++] = tolower(tag[x++]);
				}
				name_buff[i] = '\0';
				x = k;
				i = 0;
				int l = strlen( state->node->name );
				while ( x < l )
				{
					pname_buff[i++] = tolower( state->node->name[x++] );
				}
				pname_buff[i] = '\0';
				
				if ( strcmp( name_buff, pname_buff ) == 0 )
				{
					state->node = state->node->parent_node;
				}
				else
				{
					puts("xml_doc_parse error: Strict mode enabled, and closing tag doesn't match current node.");
				}
			}
			else
			{
				state->node = state->node->parent_node;
			}
			
		}
	}
}


// tagline should be the element node tag line without brackets < >
void xml_docparse_tag( struct xml_docparse_state *state, const char *tag, const int tag_len )
{
	assert( state );
	assert( state->doc );
	
	// input validity
	if ( ! ( tag && tag_len > 0 ) )
	{
		return;
	}
	
	state->in_quote = 0;
	
	// detect prolog header
	if ( tag[0] == '?' )
	{
		if ( state->node )
		{
			puts("xml_doc_parse warning: Found prolog (XML header) but not at start of file. Ignoring.");
			return;
		}
		
		if ( xml_check_xml( tag, 1 ) )
		{
			xml_docparse_header( state, tag + 4, tag_len - 4 ); // skip '?xml'
		}
		else
		{
			puts("xml_doc_parse error: Invalid prolog (XML header).");
		}
		return;
	}
	// detect closing tag
	else if ( tag[0] == '/')
	{
		// closing tag
		xml_docparse_tag_close( state, tag+1, tag_len-1 );
		return;
	}
	
	
	// REGULAR NODE
	int i = 0, k = 0;
	// skip invalid chars
	while ( i < tag_len && ! isalnum(tag[i]) )
	{
		i++;
	}
	
	char xtra_buff[XML_STRING_BUFFER_SIZE];
	
	// record valid chars (for node name)
	while ( i < tag_len && isalnum(tag[i]) )
	{
		xtra_buff[k++] = tag[i++];
	}
	xtra_buff[k] = '\0';
	
	// create XML node
	struct xml_node *node = xml_node_create( xtra_buff );
	
	// if not root node
	if ( ! state->doc->root_node )
	{
		state->doc->root_node = node;
		state->node = node;
		
	}
	else if ( state->node )
	{
		xml_node_add_child( state->node, node );
		
		int z = tag_len;
		while ( --z > 0 )
		{
			if ( isspace(tag[z]) ) continue;
			if ( tag[z] != '/' )
			{
				state->node = node;
			}
			break;
		}
	}
	else
	{
		puts("xml_doc_parse error: No node selected, but root_node is non-null.");
		xml_node_free( node, 0 );
		return;
	}
	
	// get attributes
	if ( i < tag_len )
	xml_docparse_attributes(state, node, tag + i, tag_len - i );
	
}



/**
 * @brief Parse XML data (as string) into objects.
 * @param buffer Character string to read data from.
 * @param buff_len Length of character data.
 * @returns xml_doc allocated object.
 * 
 * 
 */
struct xml_doc* xml_doc_parse( const char *x_data, const size_t x_data_len, const char strict_formatting_bool )
{
	assert( x_data );
	assert( x_data_len > 0 );
	
	struct xml_doc *doc = xml_doc_create();
	
	struct xml_docparse_state state;
	state.doc = doc;
	state.node = 0;
	state.in_quote = 0;
	state.strict = strict_formatting_bool;
	
	strbuff line_buffer;
	sb_init( &line_buffer );
	char tbody_started, c;
	
	// loop whole data string
	int i = -1;
	while ( ++i < x_data_len )
	{
		// loop until '<'
		tbody_started = 0;
		while ( i < x_data_len && ((c = x_data[i]) != '<' || state.in_quote) )
		{
			// record chars in quotes, instead of finding tag
			// otherwise just increment index (trying to find start of token)
			
			if ( isspace( c ) )
			{
				if ( tbody_started )
				{
					sb_putc( &line_buffer, c );
				}
			}
			else
			{
				// record non-space character
				sb_putc( &line_buffer, c );
				tbody_started = 1;
			}
			
			if (c == '\\')
			{
				// increment and check length
				if ( ++i >= x_data_len ) break;
				sb_putc( &line_buffer, x_data[i] );
			}
			i++;
			
		} //end while
		
		if ( i >= x_data_len )
		{
			// exceeded length of string, no node found
			break;
		}
		
		// accumulate text elements
		if ( state.node && tbody_started )
		{
			tbody_started = 0;
			sb_strip_trailing( &line_buffer );
			char *s = sb_cstr( &line_buffer );
			if ( s )
			{
				
				xml_text_append( &(state.node->text_body), s );
				_FREE( s );
			}
		}
		sb_reset( &line_buffer );
		
		// handle comments
		if ( i+3 < x_data_len && strncmp( (x_data + i), "<!--", 4 ) == 0 )
		{
			// advance index
			i += 3;
			// loop until end of data string (-2)
			while ( ++i + 2 < x_data_len )
			{
				if ( strncmp( (x_data + i), "-->", 3 ) == 0 )
				{
					// i += 2 here, but moved outside loop for comments with no end tag
					break;
				}
			} //end while
			// increment for ending processing, if comment has no end tag (at end of data)
			i += 2; // main loop increments, so 2 instead of 3
		}
		// non-comment
		else
		{
			// other bracket
			while ( ++i < x_data_len && ((c = x_data[i]) != '>' || state.in_quote) )
			{
				// record everything, including quotes
				sb_putc( &line_buffer, c );
				if ( c == '\\' )
				{
					// record extra character for escape sequence (in case it's a double quote)
					if ( ++i >= x_data_len ) break; // check line end
					sb_putc( &line_buffer, x_data[i] );
				}
				else if ( c == '\"')
				{
					// char already added, just flip quote bits
					state.in_quote = ! state.in_quote;
				}
			} //end while
			// end of string, break
			if ( i >= x_data_len )
			{
				break;
			}
			// found end of tag
			else if ( x_data[i] == '>' )
			{
				if ( ! state.in_quote )
				{
					char *tag = sb_cstr( &line_buffer );
					if ( tag )
					{
						xml_docparse_tag( &state, tag, sb_len(&line_buffer) );
						_FREE( tag );
					}
					sb_reset( &line_buffer );
				}
				
			}
		}
	} //end while
	
	sb_clear( &line_buffer );
	return doc;
}







/***********
* XML_WRITE
***********/

void xml_write_attr_text( const struct xml_text *t, FILE *file ) {
	assert( t );
	
	fputc( '"', file );
	
	if ( t->text && t->text_len > 0 )
		fwrite( t->text, t->text_len, 1, file );
	
	fputc( '"', file );
}

// prepended space
void xml_write_attribute( const struct xml_attribute *attr, FILE *file ) {
	assert( attr );
	assert( file );
	
	fputc( ' ', file );
	fwrite( attr->name, strlen(attr->name), 1, file );
	fputc( '=', file );
	xml_write_attr_text( &(attr->text_body), file );
}

void xml_write_node( const struct xml_node *node, FILE *file ) {
	assert( node );
	assert( file );
	
	const char has_text = (node->text_body.text && node->text_body.text_len > 0);
	const int len = strlen( node->name );
	
	// opening tag
	fputc( '<', file );
	fwrite( node->name, len, 1, file );
	
	// write attributes
	// for each attr...
	// hash_table.entries  key, data, next
	struct hash_table_entry *hte;
	for ( int i = 0; i < HASH_TABLE_SIZE; i++ ) {
		hte = (struct hash_table_entry*) &(node->attributes.entries[i]);
		
		if ( hte->key[0] != '\0' ) {
			while ( hte ) {
				xml_write_attribute( (struct xml_attribute*) hte->data, file );
				hte = hte->next;
			}
		}
	}
	
	if ( has_text || node->child_nodes ) {
		fputc( '>', file );
		
		// child nodes
		node_t *curr = node->child_nodes;
		while ( curr ) {
			xml_write_node( (struct xml_node*) curr->data, file );
			curr = curr->next;
		}
		
		// text body
		if ( has_text ) fwrite( node->text_body.text, node->text_body.text_len, 1, file);
		
		// closing body tag
		fputs( "</", file );
		fwrite( node->name, len, 1, file );
		fputc( '>', file );
	} else {
		// closing line tag
		fputs( " />", file );
	}
	
}

void xml_write_document( struct xml_doc *doc, FILE *file, const char include_prolog ) {
	assert( doc );
	assert( file );
	
	if ( include_prolog )
	{
		if ( doc->encoding[0] == '\0') {
			strcpy( doc->encoding, "UTF-8" );
		}
		// write header
		fprintf( file, "<?xml version=\"%i.%i\" encoding=\"%s\" ?>", doc->version_major, doc->version_minor, doc->encoding );
	}
	
	// write root node
	xml_write_node( doc->root_node, file );
	fputc( '\n', file );
}



/**
 * @brief Save a xml_doc to file. Filename must be set on @struct xml_doc.
 * @param doc 
 * @see xml_doc, xml_doc_open
 * 
 * 
 */
void xml_doc_save( struct xml_doc *doc, const char *fname )
{
	assert( doc );
	
	if ( fname && fname[0] != '\0' )
	{
		if ( ! xml_check_filename( fname, strlen(fname) ) )
		{
			puts("xml_doc_save error: Invalid file name. File not saved.");
			return;
		}
	}
	else
	{
		puts("xml_doc_save error: Empty file name. File not saved.");
	}
	
	FILE *file = fopen(fname, "w");
	if ( file )
	{
		xml_write_document( doc, file, 1 );
		fclose( file );
	}
	else
	{
		printf("xml_doc_save error: Could not open file for writing (%s).\n", fname);
		//return;
	}
}

void xml_doc_save_sans_prolog( struct xml_doc *doc, const char *fname )
{
	assert( doc );
	
	if ( fname && fname[0] != '\0' )
	{
		if ( ! xml_check_filename( fname, strlen(fname) ) )
		{
			puts("xml_doc_save (sans_prolog) error: Invalid file name. File not saved.");
			return;
		}
	}
	else
	{
		puts("xml_doc_save (sans_prolog) error: Empty file name. File not saved.");
	}
	
	FILE *file = fopen(fname, "w");
	if ( file )
	{
		xml_write_document( doc, file, 0 );
		fclose( file );
	}
	else
	{
		printf("xml_doc_save (sans_prolog) error: Could not open file for writing (%s).\n", fname);
		//return;
	}
}



/**
 * @brief 
 * @param node 
 * @param name 
 * @param value 
 * 
 * 
 */
void xml_node_set_attr( struct xml_node *node, const char *name, const char *value ) {
	assert( node ); assert( name ); assert( value );
	
	struct xml_attribute *attr = xml_node_get_attr( node, name );
	if ( !attr ) {
		// create and apply attribute
		attr = xml_attribute_create( name, value );
		xml_node_apply_attr( node, attr ); //data stored
	} else {
		// just update text
		xml_text_create( &(attr->text_body), value );
	}
}



/**
 * @brief 
 * @param node 
 * @param attr 
 * 
 * 
 */
void xml_node_apply_attr( struct xml_node *node, struct xml_attribute *attr ) {
	assert( node ); assert( attr );
	
	ht_set( &(node->attributes), attr->name, strlen(attr->name), attr);
}



/**
 * @brief 
 * @param node 
 * @param name 
 * @returns 
 * 
 * 
 */
struct xml_attribute* xml_node_get_attr( struct xml_node *node, const char *name ) {
	assert( node ); assert( name );
	
	return (struct xml_attribute*) ht_get( &(node->attributes), name, strlen(name) );
}



/**
 * @brief 
 * @param node 
 * @param name 
 * @returns 
 * 
 * 
 */
struct xml_text* xml_node_get_attr_value( struct xml_node *node, const char *name ) {
	assert( node ); assert( name );
	
	return &( xml_node_get_attr( node, name )->text_body );
}



/**
 * @brief 
 * @param parent 
 * @param child 
 * 
 * 
 */
void xml_node_add_child( struct xml_node *parent, struct xml_node *child ) {
	assert( parent );
	assert( child );
	
	child->parent_node = parent;
	node_push_back( &(parent->child_nodes), child );
}



/**
 * @brief 
 * @param parent 
 * @param child 
 * @param idx 
 * 
 * 
 */
void xml_node_insert_child_at( struct xml_node *parent, struct xml_node *child, int idx )
{
	assert( parent );
	assert( child );
	// idx < 0 means from right side
	
	node_t *n;
	
	// convert negative idx
	if ( idx < 0 )
	{
		idx = node_count( parent->child_nodes ) + idx;
		if ( idx <= 0 )
		{
			//insert at idx 0
			n = node_create( child );
			n->next = parent->child_nodes;
			parent->child_nodes = n;
			return;
		}
	}
	else if ( idx == 0 )
	{
		n = node_create( child );
		n->next = parent->child_nodes;
		parent->child_nodes = n;
		return;
	}
	
	// get first node
	n = parent->child_nodes;
	
	if (n)
	{
		for ( int i = idx - 1; n && i > 0; i-- )
		{
			n = n->next;
		}
		
		if ( n )
		{
			node_t *k = node_create( child );
			k->next = n->next;
			n->next = k;
		}
	}
	else
	{
		parent->child_nodes = node_create(child);
	}
}





