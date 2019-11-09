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
int test_strbuff_strip()
{
	// test object
	strbuff sb;
	sb_init( &sb );
	
	// put string
	sb_puts( &sb, "asdf", 4 );
	
	// get cstring
	char *s = sb_cstr( &sb );
	
	if ( assertive("sb_cstr", s != 0 && strlen(s) == 4 ) )
	{
		
		_FREE(s);
		s = 0;
		
		sb_reset( &sb );
		sb_puts( &sb, "  rofl  rofl  ", 14 );
		
		sb_strip_trailing( &sb );
		
		s = sb_cstr( &sb );
		
		if ( assertive( "sb_strip_trailing", strcmp("  rofl  rofl", s ) == 0) )
		{
			_FREE(s);
			s = 0;
			
			
			sb_clear( &sb );
			return 1;
		}
		
	}
	if (s) _FREE(s);
	s = 0;
	
	sb_clear(&sb);
	return 0;
}

int test_strbuff()
{
	
	strbuff sb;
	sb_init( &sb );
	
	// test boundary
	for ( int i = 0; i < STRBUFF_PARTITION_SIZE * 3; i++ )
	{
		sb_putc( &sb, 'a' );
	}
	
	
	
	if ( assertive("sb_len", sb_len(&sb) == STRBUFF_PARTITION_SIZE * 3) )
	{
		sb_reset( &sb );
		
		if ( assertive("sb_reset", sb_len( &sb ) == 0 ) )
		{
			sb_clear( &sb );
			
			for ( int i = 0; i < STRBUFF_PARTITION_SIZE; i++ )
			{
				sb_putc( &sb, 'b' );
			}
			
			sb_setc( &sb, 4, 'c' );
			
			assertive("sb_setc, sb_getc", sb_getc(&sb, 4) == 'c');
			
			sb_clear( &sb );
			
			return test_strbuff_strip();
		}
		
	}
	sb_clear( &sb );
	
	return 0;
}

