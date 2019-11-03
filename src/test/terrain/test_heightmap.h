
int test_heightmap()
{
	int ret = 1;
	
	const int hmap_size = 64, half_size = hmap_size >> 1;
	
	heightmap hmap;
	hm_init( &hmap, hmap_size );
	
	hm_set_elevation( &hmap, half_size, half_size, 4 );
	hm_set_flags( &hmap, half_size, half_size, 0xAE );
	
	if ( ! assertive("hmap_elev", hm_get_elevation(&hmap, half_size, half_size) == 4 ) )
	{
		printf("elev: %d\n", hm_get_elevation(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	// typecast (char) to prevent default type (int) causing false negatives.
	if ( ! assertive("hmap_flags", hm_get_flags(&hmap, half_size, half_size) == (char) 0xAE))
	{
		printf("flags: %d\n", hm_get_flags(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	if ( ! assertive("hmap_flags2", hm_get_flags(&hmap, half_size-1, half_size) != (char) 0xAE))
	{
		printf("flags: %d\n", hm_get_flags(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	hm_remove_flags( &hmap, half_size, half_size, 0xA0);
	
	if ( ! assertive("hmap_flags3", hm_get_flags(&hmap, half_size, half_size) == (char) 0x0E))
	{
		printf("flags: %d\n", hm_get_flags(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	hm_add_flags( &hmap, half_size, half_size, 0xE1);
	
	if ( ! assertive("hmap_flags4", hm_get_flags(&hmap, half_size, half_size) == (char) 0xEF))
	{
		printf("flags: %d\n", hm_get_flags(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	// test boundaries
	hm_set_elevation( &hmap, 0, 0, 2 );
	if ( ! assertive( "hm_set_elevation 0,0", hm_get_elevation( &hmap, 0,0) == 2))
	{
		ret = 0;
	}
	hm_set_elevation( &hmap, 0, hmap_size, 2 );
	if ( ! assertive( "hm_set_elevation 0,size", hm_get_elevation( &hmap, 0,hmap_size) == 2 ))
	{
		ret = 0;
	}
	hm_set_elevation( &hmap, hmap_size, 0, 2 );
	if ( ! assertive( "hm_set_elevation size,0", hm_get_elevation( &hmap, hmap_size,0) == 2 ))
	{
		ret = 0;
	}
	hm_set_elevation( &hmap, hmap_size, hmap_size, 2 );
	if ( ! assertive( "hm_set_elevation size,size", hm_get_elevation( &hmap, hmap_size,hmap_size) == 2 ))
	{
		ret = 0;
	}
	
	hm_destroy( &hmap );
	
	return ret;
}
