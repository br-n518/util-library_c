
int test_hash_e()
{
	int ret = 0;
	
	hash_table_e table;
	eht_init( &table );
	
	int data1 = 20;
	int data2 = 30;
	int data3 = 40;
	
	eht_set( &table, "asdf", 4, &data1 );
	eht_set( &table, "qwer", 4, &data2 );
	eht_set( &table, "gggg", 4, &data3 );
	eht_set( &table, "qwer", 4, &data1 );
	
	if ( eht_get( &table, "qwer", 4 ) == &data1 ) {
	
		eht_remove( &table, &data3 );
		if ( !( eht_has( &table, "gggg", 4 ) ) ) {
		
			eht_unset( &table, "asdf", 4 );
			if ( !( eht_has( &table, "asdf", 4 ) ) ) {
			
				ret = 1;
			}
		}
	}
	
	// allocates memory when keys collide, so clean up with ht_clear
	eht_clear( &table );
	
	return ret;
}
