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

