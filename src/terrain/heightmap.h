/* heightmap.h
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
#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_


#include <assert.h>

#ifdef GODOT
#	include "../gdnative/godot_sub_native.h"
#	define _MALLOC api->godot_alloc
#	define _FREE api->godot_free
#else
#	include <stdlib.h>
#	define _MALLOC malloc
#	define _FREE free
#endif



typedef struct heightmap {
	int size, hm_size; // hm_size = size+1 for inclusive borders
	int *elevation;
	char *flags;
} heightmap;



void hm_init( heightmap *map, const int size );
void hm_destroy( heightmap *map );

int hm_elevation_at( heightmap *map, const int x, const int y );
char hm_flags_at( heightmap *map, const int x, const int y );

void hm_set_elevation( heightmap *map, const int x, const int y, const int elev );
void hm_set_flags( heightmap *map, const int x, const int y, const char flags );
void hm_add_flags( heightmap *map, const int x, const int y, const char flags );
void hm_remove_flags( heightmap *map, const int x, const int y, const char flags );

#endif

