
int test_strbuff_strip()
{
	// test object
	strbuff sb;
	sb_init( &sb );
	
	// put string
	sb_puts( &sb, "asdf", 4 );
	
	// strip trailing (should do nothing)
	//sb_strip_trailing( &sb );
	
	// get cstring
	char *s = sb_cstr( &sb );
	
	if ( s != 0 )
	{
		if ( strlen(s) != 4 )
		{
			printf("len = %d not 4\n", (int) strlen(s) );
			free(s);
			return 0;
		}
		
		sb_reset( &sb );
		sb_puts( &sb, "  rofl  rofl  ", 14 );
		
		sb_strip_trailing( &sb );
		
		free(s);
		s = sb_cstr( &sb );
		
		if ( assertive( "sb_strip_trailing", strcmp("  rofl  rofl", s ) == 0) )
		{
			free(s);
			s = 0;
			
			sb_clear(&sb);
			
			for (int i = 0; i < STRBUFF_PARTITION_SIZE; i++ )
				sb_putc( &sb, 'X' );
			
			sb_puts( &sb, "    ", 4 );
			
			int l = sb_len( &sb );
			sb_strip_trailing( &sb );
			int l2 = sb_len( &sb );
			
			if ( l2 == l - 4 )
			{
				return 1;
			}
		}
		
		if (s) free(s);
		
	}
	
	sb_clear(&sb);
	return 0;
}

int test_strbuff()
{
	
	strbuff sb;
	sb_init( &sb );
	
	
	for ( int i = 0; i < STRBUFF_PARTITION_SIZE * 3; i++ )
	{
		sb_putc( &sb, 'a' );
	}
	
	if ( sb_len( &sb ) == STRBUFF_PARTITION_SIZE * 3 )
	{
		sb_reset( &sb );
		
		if ( sb_len( &sb ) == 0 )
		{
			sb_clear( &sb );
			
			for ( int i = 0; i < STRBUFF_PARTITION_SIZE; i++ )
			{
				sb_putc( &sb, 'b' );
			}
			
			sb_setc( &sb, 4, 'c' );
			
			return test_strbuff_strip();
		}
		
	}
	return 0;
}

