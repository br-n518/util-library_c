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

struct rect create_rect(int x, int y, int w, int h) {
	struct rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

void map_draw_rect(tiled_map *map, struct rect *r, char value, char mask) {
	int xx, yy, i = map->width * map->height;
	for (yy = r->y + r->h-1; yy >= r->y; yy--) {
		for (xx = r->x + r->w-1; xx >= r->x; xx--) {
			if (map->tiles[i] == mask)
				set_tile(map, xx, yy, value);
			i--;
		}
	}
}

tiled_map* init_tiled_map(int width, int height) {
	tiled_map *map = _MALLOC(sizeof(tiled_map));
	map->tiles = _MALLOC(width * height);
	for (int i = (width * height) - 1; i >= 0; i--) {
		map->tiles[i] = 0;
	}
	map->width = width;
	map->height = height;
	return map;
}


void free_tiled_map(tiled_map *map) {
	_FREE(map->tiles);
	_FREE(map);
}



void set_tile(tiled_map *map, int x, int y, char value) {
	if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
		map->tiles[(map->width * y) + x] = value;
	}
}


char get_tile(tiled_map *map, int x, int y) {
	if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
		return map->tiles[(map->width * y) + x];
	}
	return -1;
}



