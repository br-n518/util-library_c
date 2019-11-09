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
#include "dsquare_hmap.h"

#include "../rand/rnd.h"


static rnd_pcg_t dsquare_hmap_rnd;

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
	
	center = (center >> 2) + rnd_pcg_range( &dsquare_hmap_rnd,1, roughness);
	
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
		hm_set_elevation( map, x + half_size, y, (a >> 2) + rnd_pcg_range( &dsquare_hmap_rnd,1, roughness) );
	}
	// EAST
	if ( hm_get_elevation( map, x + size, y + half_size ) == 0 ) {
		a = (
				hm_get_elevation( map, x + size, y + size ) + //SE
				hm_get_elevation( map, x + size, y ) + //NE
				center + center
				);
		hm_set_elevation( map, x + size, y + half_size, (a >> 2) + rnd_pcg_range( &dsquare_hmap_rnd,1, roughness) );
	}
	// SOUTH
	if ( hm_get_elevation( map, x + half_size, y + size ) == 0 ) {
		a = (
				hm_get_elevation( map, x, y + size ) + //SW
				hm_get_elevation( map,  x + size, y + size ) + //SE
				center + center
				);
		hm_set_elevation( map, x + half_size, y + size, (a >> 2) + rnd_pcg_range( &dsquare_hmap_rnd,1, roughness) );
	}
	// WEST
	if ( hm_get_elevation( map, x, y + half_size ) == 0 ) {
		a = (
				hm_get_elevation( map, x, y ) + //NW
				hm_get_elevation( map, x, y + size ) + //SW
				center + center
				);
		hm_set_elevation( map, x, y + half_size, (a >> 2) + rnd_pcg_range( &dsquare_hmap_rnd, 1, roughness) );
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



void dsquare_hmap( heightmap *map, const unsigned int seed, const int max_initial_height, const char roughness ) {
	assert( map );
	assert( max_initial_height > 0 );
	
	// seed RNG
	//R_ranlux_seed( seed );
	rnd_pcg_seed( &dsquare_hmap_rnd, seed );
	
	// set 4 initial corners, then average and rough the rest recursively
	hm_set_elevation( map, 0, 0, rnd_pcg_range( &dsquare_hmap_rnd, 1, max_initial_height) );
	hm_set_elevation( map, map->size, 0, rnd_pcg_range( &dsquare_hmap_rnd, 1, max_initial_height) );
	hm_set_elevation( map, 0, map->size, rnd_pcg_range( &dsquare_hmap_rnd, 1, max_initial_height) );
	hm_set_elevation( map, map->size, map->size, rnd_pcg_range( &dsquare_hmap_rnd, 1, max_initial_height) );
	
	dsquare( map, 0, 0, map->size, roughness );
}




