
int test_heightmap()
{
	int ret = 1;
	
	const int hmap_size = 64, half_size = hmap_size >> 1;
	
	heightmap hmap;
	hm_init( &hmap, hmap_size );
	
	hm_set_elevation( &hmap, half_size, half_size, 4 );
	hm_set_flags( &hmap, half_size, half_size, 0xAE );
	
	if ( ! assertive("hmap_elev", hm_elevation_at(&hmap, half_size, half_size) == 4 ) )
	{
		printf("elev: %d\n", hm_elevation_at(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	if ( ! assertive("hmap_flags", hm_flags_at(&hmap, half_size, half_size) == (char) 0xAE))
	{
		printf("flags: %d\n", hm_flags_at(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	if ( ! assertive("hmap_flags2", hm_flags_at(&hmap, half_size-1, half_size) != (char) 0xAE))
	{
		printf("flags: %d\n", hm_flags_at(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	hm_remove_flags( &hmap, half_size, half_size, 0xA0);
	
	if ( ! assertive("hmap_flags3", hm_flags_at(&hmap, half_size, half_size) == (char) 0x0E))
	{
		printf("flags: %d\n", hm_flags_at(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	hm_add_flags( &hmap, half_size, half_size, 0xE1);
	
	if ( ! assertive("hmap_flags4", hm_flags_at(&hmap, half_size, half_size) == (char) 0xEF))
	{
		printf("flags: %d\n", hm_flags_at(&hmap, half_size, half_size) );
		ret = 0;
	}
	
	// TODO test boundaries
	
	hm_destroy( &hmap );
	
	return ret;
}
