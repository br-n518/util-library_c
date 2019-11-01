
int test_vector_str() {
	int ret = 1;
	
	vector_str s;
	vs_init( &s );
	
	char testc[] = "Asdf";
	vs_set( &s, testc );
	
	// test vs_length(), vs_char_at(), and vs_index_of_*() (string: Asdf)
	if ( ! assertive( "vs_length, char_at, index_of_*", vs_test( &s, testc ) &&
				vs_length(&s) == 4 &&
				vs_char_at( &s, 0 ) == 'A' &&
				vs_char_at( &s, 1 ) == 's' &&
				vs_index_of_c( &s, 's' ) == 1 &&
				vs_index_of_s( &s, "df" ) == 2 ) ) {
		ret = 0;
	}
	else
	{
		// test insert (Asdf)
		vs_insert( &s, "EE", 1 ); //middle
		vs_insert( &s, "WW", 0 ); //front
		vs_insert( &s, "a", 8 ); //end
		// WWAEEsdfa
		
		if ( ! assertive("vs_insert", vs_test( &s, "WWAEEsdfa" ) ) )
		{
			ret = 0;
		}
		else
		{
			// test replace middle (WWAEEsdfa)
			vs_replace( &s, "EE", "AA" );
			
			if ( ! assertive("vs_replace mid", vs_test( &s, "WWAAAsdfa")))
			{
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			
			// test replace middle with empty (WWAAAsdfa)
			vs_replace( &s, "AAA", "" );
			
			if ( ! assertive("vs_replace empty", vs_test( &s, "WWsdfa" )) )
			{
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			
			// test replace full string (WWsdfa)
			vs_replace( &s, "WWsdfa", "" );
			
			if ( ! assertive("vs_replace full", vs_test( &s, "" )) )
			{
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			// test replace end
			vs_set( &s, "Asdf" );
			vs_replace( &s, "sdf", "SDF" );
			
			if ( ! assertive("vs_replace end", vs_test( &s, "ASDF" ) ) )
			{
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			
			// set string for testing replace_idx
			vs_set( &s, "ABABCBCB");
			// test search from index -1
			vs_replace_idx( &s, "AB", "XX", 1);
			
			if ( ! assertive("vs_replace_idx 1", vs_test( &s, "ABXXCBCB")))
			{
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			
			// search from index 0
			vs_replace_idx( &s, "A", "Y", 0);
			
			if ( ! assertive("vs_replace_idx 2", vs_test( &s, "YBXXCBCB")))
			{
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			
			// search from index -1
			vs_replace_idx( &s, "B", "Y", 0);
			
			if ( ! assertive("vs_replace_idx 3", vs_test( &s, "YYXXCBCB")))
			{
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			
			// search from index 0
			vs_replace_idx( &s, "B", "Y", 5);
			
			if ( ! assertive("vs_replace_idx 4", vs_test( &s, "YYXXCYCB"))) //result YCB ???
			{
				char *cs = vs_cstr(&s);
				puts( cs );
				_FREE( cs );
				ret = 0;
				goto CLABEL_test_vec_str_end;
			}
			
		}
	}
	
	CLABEL_test_vec_str_end:
	
	vs_destroy( &s );
	
	return ret;
}

