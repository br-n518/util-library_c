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

#include <assert.h>

#include "../alloc.h"



struct rect {
	int x, y, w, h;
};

typedef struct tiled_map {
	char *tiles;
	int width, height;
	//struct rect bounds
} tiled_map;



#ifdef __cplusplus
extern "C" {
#endif



struct rect create_rect(const int x, const int y, const int w, const int h);

// draw rect, but only overwrite tiles matching "mask" value
void map_draw_rect(tiled_map *map, struct rect *r, const char value, const char mask);

// initial value for tiles: 0
tiled_map* create_tiled_map(const int width, const int height);
void free_tiled_map(tiled_map *map);


void set_tile(tiled_map *map, const int x, const int y, const char value);
char get_tile(tiled_map *map, const int x, const int y);

#ifdef __cplusplus
}
#endif



#endif

