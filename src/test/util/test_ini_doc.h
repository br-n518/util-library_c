
int test_ini_doc()
{
	
	struct ini_doc *ddoc = _MALLOC( sizeof(*ddoc) );
	ini_doc_init( ddoc );
	
	char ret = ini_doc_load( ddoc, "test/test.ini" );
	
	if ( ret )
	{
		ini_doc_set_global( ddoc, "monkey", "Mankey");
		
		ini_doc_set( ddoc, "asdf", "elephant", "donphan" );
		
		ini_doc_save( ddoc, "test/result__test.ini" );
		
		ret = 0;
		if ( strcmp( ini_doc_get(ddoc,"asdf","elephant"), "donphan" ) == 0 )
		{
			if ( strcmp( ini_doc_get_global(ddoc,"monkey"), "Mankey" ) == 0 )
			{
				ret = 1;
			}
		}
		
		
	}
	
	ini_doc_destroy( ddoc );
	_FREE( ddoc );
	
	return ret;
}


