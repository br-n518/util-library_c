/* octree.h
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
#ifndef OCTREE_H_
#define OCTREE_H_

#include <string.h>
#include "../util/node.h"

#include "../alloc.h"

#define OCTREE_CELL_SOLID 1
#define OCTREE_CELL_SPLIT 2
#define OCTREE_CELL_PARENT 3

#define OCTREE_CELL_START 4
#define OCTREE_CELL_END 8

#define OCTREE_NBOR_X_POS 0
#define OCTREE_NBOR_X_NEG 1
#define OCTREE_NBOR_Y_POS 2
#define OCTREE_NBOR_Y_NEG 3
#define OCTREE_NBOR_Z_POS 4
#define OCTREE_NBOR_Z_NEG 5

typedef struct octree_cell {
	struct octree_cell *cells[8];
	struct octree_cell *nbors[6];
	int size, x, y, z;
	char flags;
} octree_cell;

// wrapper type
typedef struct octree {
	octree_cell *root;
} octree;


#ifdef GODOT
	// for octree_cell_render
	typedef struct octree_mesh {
		godot_pool_vector3_array verts;
		godot_pool_vector2_array uvs;
	} octree_mesh;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef GODOT
	void octree_mesh_init( octree_mesh *m );
	void octree_mesh_destroy( octree_mesh *m );

	void octree_cell_render( octree_cell *c, octree_mesh *floors, octree_mesh *walls, octree_mesh *ceilings );
#endif


void octree_init( octree *g, const int size );
void octree_destroy( octree *g );

void octree_cell_set( octree_cell *c );

// vertical Y axis (for Godot)
octree_cell* octree_get( octree *g, const int x, const int y, const int z );


//void octree_assign_neighbors( octree_cell *c ); // applies to child cells of @p c
void octree_cell_split( octree_cell *c );
void octree_cell_split_n( octree_cell *c, const int n );
void octree_cell_split_to( octree_cell *c, const int target_size );

octree_cell* octree_cut_point( octree *g, const int x, const int y, const int z );

#ifdef __cplusplus
}
#endif



#endif



