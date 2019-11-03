/* tiled_map.c
 *
 * Copyright (c) 2019 br-n518
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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



