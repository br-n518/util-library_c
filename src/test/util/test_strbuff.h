
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

