
int test_split_tmd()
{
	int ret = 1;
	
	tiled_map *map = create_tiled_map(64, 64);
	
	tmd_split_dungeon( map, 2 );
	
	if ( ! (get_tile(map, 2, 2) != 0 || get_tile(map, 4, 4) != 0 ||
			get_tile(map, 2, 4) != 0 || get_tile(map, 3, 6) != 0 ))
	{
		ret = 0;
	}
	
	int x = 1, y = 0;
	const char initial = get_tile(map, 0, 0);
	while ( get_tile(map, x, y) == initial )
	{
		x++;
		if ( x >= map->width )
		{
			x = 0;
			y++;
			
			if ( y >= map->height )
			{
				ret = 0;
				break;
			}
		}
	}
	
	
	free_tiled_map(map);
	
	return ret;
}

