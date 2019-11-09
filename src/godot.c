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
#include "gdnative/godot_native.h"

#include "alloc.h"



#include "pcg/dsquare_hmap.h"

godot_variant dungeon_dsquare(void *data, godot_array *args) {
	// args
	int size = api->godot_variant_as_int(
			api->godot_array_operator_index_const(args, 0));
			
	unsigned int seed = api->godot_variant_as_uint(
			api->godot_array_operator_index_const(args, 1));
	
	unsigned int rough = api->godot_variant_as_uint(
			api->godot_array_operator_index_const(args, 2));
	
	if ( size <= 1 ) {
		GD_PRINT("dungeon_dsquare: size (arg 0) should be >= 2 (and a power of base 2).")
	}
	
	heightmap hmap;
	hm_init( &hmap, size );
	int s = hmap.hm_size * hmap.hm_size;
	
	dsquare_hmap( &hmap, seed, 200, rough );
	
	godot_pool_byte_array pba;
	api->godot_pool_byte_array_new( &pba );
	
	// create array
	for ( int i = 0; i < s; i++ ) {
		api->godot_pool_byte_array_append( &pba, hmap.elevation[i] );
	}
	
	hm_destroy( &hmap );
	
	godot_variant ret;
	api->godot_variant_new_pool_byte_array( &ret, &pba );
	api->godot_pool_byte_array_destroy( &pba );
	
	return ret;
}


#include "pcg/octree_turtle.h"

// return variant (Array)
godot_variant dungeon_octree_turtle(void *data, godot_array *args) {
	// args
	int size = api->godot_variant_as_int(
			api->godot_array_operator_index_const(args, 0));
			
	unsigned int seed = api->godot_variant_as_uint(
			api->godot_array_operator_index_const(args, 1));
	
	if ( size <= 1 ) {
		GD_PRINT("dungeon_octree_turtle: size (arg 0) should be >= 2")
		GD_RETURN_NIL()
	}
	
	// variables
	godot_variant ret;
	godot_array arr; //store vertex arrays in array
	api->godot_array_new( &arr );
	
	// create new octree object
	octree map;
	octree_init( &map, size ); // follow with octree_destroy
	
	// init vertex receivers
	octree_mesh floors, walls, ceilings;
	octree_mesh_init( &floors ); // follow with octree_mesh_destroy
	octree_mesh_init( &walls );
	octree_mesh_init( &ceilings );
	
	// split octree
	octree_cell_split_to( map.root, 2 );
	
	// create turtle object
	// initialize at top of map, allowing turtle to draw down (no drawing up)
	octree_turtle turtle;
	ot_init( &turtle, octree_get( &map, size >> 1, size - 2, size >> 1 ), TURTLE_NORTH);
	// size - 1 breaks, need -2
	
	
	// create grammar
	node_t *rules = 0;
	push_grammar_rule( &rules, "F", "F+F-F-F+F" );
	
	switch ( seed ) {
		case 0:
			push_grammar_rule( &rules, "+F", "[+FDFF]" );
			break;
		case 1:
			push_grammar_rule( &rules, "F-", "-[F-F]" );
			push_grammar_rule( &rules, "F+", "-[F+FF]" );
			break;
		case 2:
			push_grammar_rule( &rules, "F-", "-[-F]F" );
			break;
		case 3:
			// stairway to hell
			push_grammar_rule( &rules, "F+F", "FDDFFD" );
			break;
		case 4:
			// pyramid
			push_grammar_rule( &rules, "F", "[+DFF]" );
			break;
	}
	
	// run grammar for 3 iterations with 1 rule
	char *result = create_grammar_str( "F", rules, 3 );
	
	destroy_grammar( rules );
	
	// + is actually turn_left and - is turn_right
	// octree is inverted somehow... up is down and all else.
	// push and pop [ ] work as expected.
	// draw to octree assigned to turtle
	ot_str_routine( &turtle, result );

	ot_destroy( &turtle );
	
	// render and cleanup octree
	octree_cell_render( map.root, &floors, &walls, &ceilings );
	octree_destroy( &map );
	
	// temporarily use 'ret' to add data to 'arr', which later becomes 'ret'
	api->godot_variant_new_pool_vector3_array( &ret, &(floors.verts) );
	api->godot_array_append( &arr, &ret );
	api->godot_variant_new_pool_vector2_array( &ret, &(floors.uvs) );
	api->godot_array_append( &arr, &ret );
	api->godot_variant_new_pool_vector3_array( &ret, &(walls.verts) );
	api->godot_array_append( &arr, &ret );
	api->godot_variant_new_pool_vector2_array( &ret, &(walls.uvs) );
	api->godot_array_append( &arr, &ret );
	api->godot_variant_new_pool_vector3_array( &ret, &(ceilings.verts) );
	api->godot_array_append( &arr, &ret );
	api->godot_variant_new_pool_vector2_array( &ret, &(ceilings.uvs) );
	api->godot_array_append( &arr, &ret );
	
	// delete vector arrays (as they are now converted to variants in returning array)
	octree_mesh_destroy( &floors );
	octree_mesh_destroy( &walls );
	octree_mesh_destroy( &ceilings );
	
	// create variant from array; cleanup array
	api->godot_variant_new_array( &ret, &arr );
	api->godot_array_destroy( &arr );
	
	return ret;
}



#include "pcg/split_tiled_map_drawer.h"

// return variant (PoolByteArray)
godot_variant dungeon_split_tiled_map(void *data, godot_array *args) {
	// args
	int width = api->godot_variant_as_int(
			api->godot_array_operator_index_const(args, 0));
			
	int height = api->godot_variant_as_int(
			api->godot_array_operator_index_const(args, 1));
			
	unsigned int seed = api->godot_variant_as_uint(
			api->godot_array_operator_index_const(args, 2));
	
	// create random map
	tiled_map *m = create_tiled_map(width, height);
	tmd_split_dungeon( m, seed );
	
	// variables
	godot_variant ret;
	godot_pool_byte_array arr;
	
	// create pool byte array
	api->godot_pool_byte_array_new(&arr);
	
	// fill array
	int i, l = width * height;
	for (i = 0; i < l; i++) {
		api->godot_pool_byte_array_push_back(&arr, m->tiles[i]);
	}
	
	// free map resource
	free_tiled_map(m);
	
	// apply to variant
	api->godot_variant_new_pool_byte_array(&ret, &arr);
	
	// destroy pool byte array
	api->godot_pool_byte_array_destroy(&arr);
	
	return ret;
}


