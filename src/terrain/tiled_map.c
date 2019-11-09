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
#include "tiled_map.h"

struct rect create_rect(const int x, const int y, const int w, const int h) {
	struct rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

/**
 * @brief Fill the tiled_map area given by rect @p r using @p value to change tiles matching @p mask.
 * @param map tiled_map to modify.
 * @param r rect for area to modify.
 * @param value New value for matching tiles.
 * @param mask Tile value mask. Only tiles matching @p mask will be changed.
 * @see set_tile
 * @see get_tile
 * 
 */
void map_draw_rect(tiled_map *map, struct rect *r, const char value, const char mask)
{
	assert( map );
	assert( r );
	
	int xx, yy, i = (map->width * map->height) - 1;
	for (yy = r->y + r->h-1; yy >= r->y; yy--) {
		for (xx = r->x + r->w-1; xx >= r->x; xx--) {
			if (map->tiles[i] == mask)
				set_tile(map, xx, yy, value);
			i--;
		}
	}
}

tiled_map* create_tiled_map(const int width, const int height)
{
	assert( width > 0 );
	assert( height > 0 );
	
	tiled_map *map = _MALLOC(sizeof(tiled_map));
	map->tiles = _MALLOC(width * height);
	for (int i = (width * height) - 1; i >= 0; i--) {
		map->tiles[i] = 0;
	}
	map->width = width;
	map->height = height;
	return map;
}


void free_tiled_map(tiled_map *map)
{
	assert( map );
	
	_FREE(map->tiles);
	_FREE(map);
}



void set_tile(tiled_map *map, const int x, const int y, const char value)
{
	assert( map );
	
	if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
		map->tiles[(map->width * y) + x] = value;
	}
}


char get_tile(tiled_map *map, const int x, const int y)
{
	assert( map );
	
	if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
		return map->tiles[(map->width * y) + x];
	}
	return -1;
}



