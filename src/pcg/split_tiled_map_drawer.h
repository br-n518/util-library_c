/* split_tiled_map_drawer.h
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

unsigned int tmd_get_start_x();
unsigned int tmd_get_start_y();

#ifdef __cplusplus
}
#endif

#endif

