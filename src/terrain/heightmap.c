/* heightmap.c
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
#include "heightmap.h"


// macro
/**
 * @brief 
 * @param x 
 * @param y 
 * @param w 
 * @returns 
 * 
 * 
 */
#define HM_IDX(x,y,w) ((y*w)+x)




/**
 * @brief Initialize a heightmap object.
 * @param map heightmap object to initialize.
 * @param size Size of heightmap object. Must be at least 2.
 * 
 * 
 */
void hm_init( heightmap *map, const int size ) {
	assert( map );
	assert( size >= 2 );
	
	map->size = size;
	
	int s = size + 1;
	map->hm_size = s;
	s = (s * s);
	
	map->elevation = _MALLOC( sizeof(int) * s );
	map->flags = _MALLOC( s );
	
	for (int i = 0; i < s; i++) {
		map->elevation[i] = 0;
		map->flags[i] = 0;
	}
}

/**
 * @brief Free contents of heightmap.
 * @param map heightmap to destroy.
 * 
 * 
 */
void hm_destroy( heightmap *map ) {
	assert( map );
	
	_FREE( map->elevation );
	_FREE( map->flags );
}






/**
 * @brief Get elevation at given coordinates in heightmap.
 * @param map heightmap to use.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @returns The elevation found at given coordinates.
 * 
 */
int hm_get_elevation( heightmap *map, const int x, const int y ) {
	assert( map );
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < map->hm_size );
	assert( y < map->hm_size );
	
	return map->elevation[ HM_IDX(x, y, map->hm_size) ];
}

/**
 * @brief Get applied flags for given coordinates.
 * @param map heightmap to use.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @returns Returns bit flags for given coordinates.
 * 
 * 
 */
char hm_get_flags( heightmap *map, const int x, const int y ) {
	assert( map );
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < map->hm_size );
	assert( y < map->hm_size );
	
	return map->flags[ HM_IDX(x, y, map->hm_size) ];
}






/**
 * @brief Set elevation at given coordinates.
 * @param map heightmap to modify.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param elev New elevation.
 * 
 * 
 */
void hm_set_elevation( heightmap *map, const int x, const int y, const int elev ) {
	assert( map );
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < map->hm_size );
	assert( y < map->hm_size );
	
	map->elevation[ HM_IDX(x, y, map->hm_size) ] = elev;
}






/**
 * @brief Set bit flags for coordinate.
 * @param map 
 * @param x 
 * @param y 
 * @param flags 
 * 
 * 
 */
void hm_set_flags( heightmap *map, const int x, const int y, const char flags ) {
	assert( map );
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < map->hm_size );
	assert( y < map->hm_size );
	
	map->flags[ HM_IDX(x, y, map->hm_size) ] = flags;
}

/**
 * @brief Add bit flags for coordinate.
 * @param map heightmap to modify.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param flags New bit flags to bitwise OR in.
 * 
 * 
 */
void hm_add_flags( heightmap *map, const int x, const int y, const char flags ) {
	assert( map );
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < map->hm_size );
	assert( y < map->hm_size );
	
	map->flags[ HM_IDX(x, y, map->hm_size) ] |= flags;
}

/**
 * @brief Remove selected bit flags from coordinate.
 * @param map heightmap to modify.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param flags Bits to be removed from flag.
 * 
 * 
 */
void hm_remove_flags( heightmap *map, const int x, const int y, const char flags ) {
	assert( map );
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < map->hm_size );
	assert( y < map->hm_size );
	
	map->flags[ HM_IDX(x, y, map->hm_size) ] &= ~flags;
}



