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
#ifndef HEIGHTMAP_H_
#define HEIGHTMAP_H_


#include <assert.h>


#include "../alloc.h"



typedef struct heightmap {
	int size, hm_size; // hm_size = size+1 for inclusive borders
	int *elevation;
	char *flags;
} heightmap;

#ifdef __cplusplus
extern "C" {
#endif

void hm_init( heightmap *map, const int size );
void hm_destroy( heightmap *map );

int hm_get_elevation( heightmap *map, const int x, const int y );
char hm_get_flags( heightmap *map, const int x, const int y );

void hm_set_elevation( heightmap *map, const int x, const int y, const int elev );
void hm_set_flags( heightmap *map, const int x, const int y, const char flags );
void hm_add_flags( heightmap *map, const int x, const int y, const char flags );
void hm_remove_flags( heightmap *map, const int x, const int y, const char flags );

#ifdef __cplusplus
}
#endif

#endif

