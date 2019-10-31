/* octree_turtle.h
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
#ifndef OCTREE_TURTLE_H_
#define OCTREE_TURTLE_H_

#include <string.h>
#include "../util/node.h"
#include "../util/grammar.h"
#include "../terrain/octree.h"

#ifdef GODOT
#	include "../gdnative/godot_sub_native.h"
#endif

// first two bits (number range)
#define TURTLE_NORTH 0
#define TURTLE_EAST 1
#define TURTLE_SOUTH 2
#define TURTLE_WEST 3

// next two bits (bit flags)
#define TURTLE_DOWN 4
#define TURTLE_UP 8

// 4 bits free (bit 16, 32, 64, and 128)

typedef struct octree_turtle {
	octree_cell *current_cell;
	node_t *cell_stack;
	node_t *direction_stack;
	char flags;
} octree_turtle;


#ifdef GODOT_GDNATIVE_API_STRUCT_H
	// for octree_cell_render
	typedef struct octree_mesh {
		godot_pool_vector3_array verts;
		godot_pool_vector2_array uvs;
	} octree_mesh;

	void octree_mesh_init( octree_mesh *m );
	void octree_mesh_destroy( octree_mesh *m );

	void octree_cell_render( octree_cell *c, octree_mesh *floors, octree_mesh *walls, octree_mesh *ceilings );
#endif


void ot_init( octree_turtle *t, octree_cell *start_cell, const char start_direction );
void ot_destroy( octree_turtle *t );

void ot_move_down( octree_turtle *t, const char n );
void ot_move_forward( octree_turtle *t, const char n );

void ot_set_direction( octree_turtle *t, const char direction );

char ot_get_direction( octree_turtle *t );

void ot_turn_right( octree_turtle *t );
void ot_turn_left( octree_turtle *t );

void ot_push_cell( octree_turtle *t );
void ot_pop_cell( octree_turtle *t );

void ot_str_routine( octree_turtle *t, const char *s );

#endif

