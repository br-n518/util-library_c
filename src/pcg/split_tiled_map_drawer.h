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
#ifndef SPLIT_TILED_MAP_DRAWER_H_
#define SPLIT_TILED_MAP_DRAWER_H_

#include "../terrain/tiled_map.h"

#include "../alloc.h"

#ifdef __cplusplus
extern "C" {
#endif

// room size 3 is messy, some empty rooms
#ifndef TMD_MIN_ROOM_SIZE
#	define TMD_MIN_ROOM_SIZE 4
#endif

#define TMD_ROOM_TILE 1
#define TMD_TUNNEL_TILE 1

#define TMD_EXIT_TILE 2
#define TMD_ENEMY_TILE 5
unsigned int ENEMY_COUNTER; //can't initialize...

// draw a binary tree split map to given tiled_map
void tmd_split_dungeon(tiled_map *map, unsigned int seed);

int tmd_get_start_x();
int tmd_get_start_y();

#ifdef GODOT
godot_variant tmd_get_start(void *data, godot_array *args); //returns Vector2 (godot_vector2)
#endif

#ifdef __cplusplus
}
#endif

#endif

