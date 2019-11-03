/* dsquare_hmap.c
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
#include "dsquare_hmap.h"
#include "../rand/rand.h"


// initialize all elevations to zero, use as detection
// heightmap must init all zero, and size must be a power of base 2 (uses bit shifts instead of divide, although much mod)
// Additionally, heightmap storage size is +1, for even splitting (typical hmap though, size+1 internal)


// unexposed function
void dsquare( heightmap *map, const int x, const int y, const int size, const char roughness ) {
	
	const int half_size = size >> 1;
	
	// get center
	int center = (
			hm_get_elevation( map, x, y ) +
			hm_get_elevation( map, x+size, y ) +
			hm_get_elevation( map, x, y+size ) +
			hm_get_elevation( map, x+size, y+size )
			);
	
	center = (center >> 2) + 1 + (int) (R_ranlux_get() % roughness);
	
	// DIAMOND STEP
	hm_set_elevation( map, x + half_size, y + half_size, center );
	
	// SQUARE STEP
	int a;
	// NORTH
	if ( hm_get_elevation( map, x + half_size, y ) == 0 ) {
		a = (
				hm_get_elevation( map, x, y ) + //NW
				hm_get_elevation( map, x + size, y ) + //NE
				center + center
				);
		a = (a >> 2) + (int) (R_ranlux_get() % roughness);
		hm_set_elevation( map, x + half_size, y, a + 1 );
	}
	// EAST
	if ( hm_get_elevation( map, x + size, y + half_size ) == 0 ) {
		a = (
				hm_get_elevation( map, x + size, y + size ) + //SE
				hm_get_elevation( map, x + size, y ) + //NE
				center + center
				);
		a = (a >> 2) + (int) (R_ranlux_get() % roughness);
		hm_set_elevation( map, x + size, y + half_size, a + 1 );
	}
	// SOUTH
	if ( hm_get_elevation( map, x + half_size, y + size ) == 0 ) {
		a = (
				hm_get_elevation( map, x, y + size ) + //SW
				hm_get_elevation( map,  x + size, y + size ) + //SE
				center + center
				);
		a = (a >> 2) + (int) (R_ranlux_get() % roughness);
		hm_set_elevation( map, x + half_size, y + size, a + 1 );
	}
	// WEST
	if ( hm_get_elevation( map, x, y + half_size ) == 0 ) {
		a = (
				hm_get_elevation( map, x, y ) + //NW
				hm_get_elevation( map, x, y + size ) + //SW
				center + center
				);
		a = (a >> 2) + (int) (R_ranlux_get() % roughness);
		hm_set_elevation( map, x, y + half_size, a + 1 );
	}
	
	// 8x8 map
	// half 4, 4+4 = 8 (OK) 0+4 = 4 (OK)
	// half 2, 0+2 2+2
	// elevation should never be zero, so +1 all hm_set_elevation calls
	// half 1, 0+1 1+1
	
	if (size >= 2) {
		dsquare( map, x, y, half_size, roughness );
		dsquare( map, x + half_size, y, half_size, roughness );
		dsquare( map, x, y + half_size, half_size, roughness );
		dsquare( map, x + half_size, y + half_size, half_size, roughness );
	}
}



void dsquare_hmap( heightmap *map, const int seed, const int max_initial_height, const char roughness ) {
	assert( map );
	assert( max_initial_height > 0 );
	
	// seed RNG
	R_ranlux_seed( seed );
	
	// set 4 initial corners, then average and rough the rest recursively
	hm_set_elevation( map, 0, 0, (R_ranlux_get() % max_initial_height) + 1 );
	hm_set_elevation( map, map->size, 0, (R_ranlux_get() % max_initial_height) + 1 );
	hm_set_elevation( map, 0, map->size, (R_ranlux_get() % max_initial_height) + 1 );
	hm_set_elevation( map, map->size, map->size, (R_ranlux_get() % max_initial_height) + 1 );
	
	dsquare( map, 0, 0, map->size, roughness );
}




