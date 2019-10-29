
int test_hash() {
	int ret = 0;
	
	hash_table table;
	ht_init( &table );
	
	int data1 = 20;
	int data2 = 30;
	int data3 = 40;
	
	ht_set( &table, "asdf", 4, &data1 );
	ht_set( &table, "qwer", 4, &data2 );
	ht_set( &table, "gggg", 4, &data3 );
	ht_set( &table, "qwer", 4, &data1 );
	
	if ( ht_get( &table, "qwer", 4 ) == &data1 ) {
	
		ht_remove( &table, &data3 );
		if ( !( ht_has( &table, "gggg", 4 ) ) ) {
		
			ht_unset( &table, "asdf", 4 );
			if ( !( ht_has( &table, "asdf", 4 ) ) ) {
			
				ret = 1;
			}
		}
	}
	
	// allocates memory when keys collide, so clean up with ht_clear
	ht_clear( &table );
	
	return ret;
}


