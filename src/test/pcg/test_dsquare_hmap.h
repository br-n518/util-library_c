
int test_dsquare_hmap()
{
	int ret = 1;
	
	heightmap hmap;
	hm_init( &hmap, 32 );
	
	if ( ! assertive("hm_init", hm_elevation_at(&hmap, 2, 2) == 0 ) )
	{
		ret = 0;
	}
	
	dsquare_hmap( &hmap, 2, 10, 9 );
	
	// TODO check results
	if ( ! assertive("dsquare", hm_elevation_at(&hmap, 2, 2) ) )
	{
		ret = 0;
	}
	
	hm_destroy( &hmap );
	
	return ret;
}

