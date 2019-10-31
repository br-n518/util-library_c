
int test_dsquare_hmap()
{
	int ret = 0;
	
	heightmap hmap;
	hm_init( &hmap, 32 );
	
	dsquare_hmap( &hmap, 2, 10, 9 );
	
	// TODO check results
	
	hm_destroy( &hmap );
	
	return ret;
}

