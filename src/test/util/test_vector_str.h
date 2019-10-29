
int test_vector_str() {
	int ret = 1;
	
	vector_str s;
	vs_init( &s );
	
	char testc[] = "Asdf";
	vs_set( &s, testc );
	
	// test vs_length(), vs_char_at(), and vs_index_of_*() (string: Asdf)
	if ( !( vs_test( &s, testc ) &&
				vs_length(&s) == 4 &&
				vs_char_at( &s, 0 ) == 'A' &&
				vs_char_at( &s, 1 ) == 's' &&
				vs_index_of_c( &s, 's' ) == 1 &&
				vs_index_of_s( &s, "df" ) == 2 ) ) {
		ret = 0;
	}
	
	if ( ret ) {
		 // test insert (Asdf)
		vs_insert( &s, "EE", 1 ); //middle
		vs_insert( &s, "WW", 0 ); //front
		vs_insert( &s, "a", 8 ); //end
		// WWAEEsdfa
		ret = vs_test( &s, "WWAEEsdfa" );
		
		if ( ret ) {
			// test replace middle (WWAEEsdfa)
			vs_replace( &s, "EE", "AA" );
			ret = vs_test( &s, "WWAAAsdfa");
			if (ret) {
				// test replace middle with empty (WWAAAsdfa)
				vs_replace( &s, "AAA", "" );
				ret = vs_test( &s, "WWsdfa" );
				if (ret) {
					// test replace full string (WWsdfa)
					vs_replace( &s, "WWsdfa", "" );
					ret = vs_test( &s, "" );
					if (ret) {
						// test replace end
						vs_set( &s, "Asdf" );
						vs_replace( &s, "sdf", "SDF" );
						ret = vs_test( &s, "ASDF" );
					}
				}
			}
		}
	}
	
	vs_destroy( &s );
	
	return ret;
}

