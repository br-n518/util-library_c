/*
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org>
 */
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

