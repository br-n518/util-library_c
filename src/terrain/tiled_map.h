/* tiled_map.h
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
#ifndef TILED_MAP_H_
#define TILED_MAP_H_



#ifdef GODOT
#	include "../gdnative/godot_sub_native.h"
#	define _MALLOC api->godot_alloc
#	define _FREE api->godot_free
#else
#	include <stdlib.h>
#	define _MALLOC malloc
#	define _FREE free
#endif



struct rect {
	int x, y, w, h;
};

struct rect create_rect(int x, int y, int w, int h);

typedef struct tiled_map {
	char *tiles;
	int width, height;
	//struct rect bounds
} tiled_map;

// draw rect, but only overwrite tiles matching "mask" value
void map_draw_rect(tiled_map *map, struct rect *r, char value, char mask);

// initial value for tiles: 0
tiled_map* init_tiled_map(int width, int height);
void free_tiled_map(tiled_map *map);


void set_tile(tiled_map *map, int x, int y, char value);
char get_tile(tiled_map *map, int x, int y);



#endif
