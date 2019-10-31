
int test_tiled_map()
{
	int ret = 0;
	
	tiled_map *m = init_tiled_map( 40, 40 );
	
	
	set_tile( m, 0, 0, 1 );
	
	struct rect r = (struct rect) create_rect(1, 1, 5, 5);
	map_draw_rect( m, &r, 2, 0 );
	
	if ( get_tile( m, 2, 2 ) == 2 && get_tile( m, 1, 0 ) == 0 && get_tile( m, 0, 0 ) == 1 ) {
		ret = 1;
	}
	
	free_tiled_map( m );
	
	return ret;
}
