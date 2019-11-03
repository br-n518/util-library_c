/* octree.c
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
#include "octree.h"


// hidden function
void octree_assign_neighbors( octree_cell *c ) {
	assert( c );
	assert( c->flags & OCTREE_CELL_SPLIT );

	octree_cell **nbors;
	for ( int i = 0; i < 8; i++ ) {
		nbors = c->cells[i]->nbors;
		switch (i) {
			case 0:
			
				nbors[OCTREE_NBOR_X_POS] = c->cells[1];
				nbors[OCTREE_NBOR_X_NEG] = c->nbors[OCTREE_NBOR_X_NEG];
				nbors[OCTREE_NBOR_Y_POS] = c->nbors[OCTREE_NBOR_Y_POS];
				nbors[OCTREE_NBOR_Y_NEG] = c->cells[4];
				nbors[OCTREE_NBOR_Z_POS] = c->cells[2];
				nbors[OCTREE_NBOR_Z_NEG] = c->nbors[OCTREE_NBOR_Z_NEG];
				
				// adjacent cell
				if ( nbors[OCTREE_NBOR_X_NEG] ) {
					// get closest size sub-cell
					while ( nbors[OCTREE_NBOR_X_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_NEG] = nbors[OCTREE_NBOR_X_NEG]->cells[1];
					}
					// check neighbor's size and reassign their neighbor (if larger)
					if ( nbors[OCTREE_NBOR_X_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_NEG]->nbors[OCTREE_NBOR_X_POS] = c->cells[i];
					}
				}
				// adjacent cell
				if ( nbors[OCTREE_NBOR_Y_POS] ) {
					while ( nbors[OCTREE_NBOR_Y_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_POS] = nbors[OCTREE_NBOR_Y_POS]->cells[4];
					}
					if ( nbors[OCTREE_NBOR_Y_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_POS]->nbors[OCTREE_NBOR_Y_NEG] = c->cells[i];
					}
				}
				// adjacent cell
				if ( nbors[OCTREE_NBOR_Z_NEG] ) {
					while ( nbors[OCTREE_NBOR_Z_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_NEG] = nbors[OCTREE_NBOR_Z_NEG]->cells[2];
					}
					if ( nbors[OCTREE_NBOR_Z_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_NEG]->nbors[OCTREE_NBOR_Z_POS] = c->cells[i];
					}
				}
				
				break;
				
			case 1:
			
				nbors[OCTREE_NBOR_X_POS] = c->nbors[OCTREE_NBOR_X_POS];
				nbors[OCTREE_NBOR_X_NEG] = c->cells[0];
				nbors[OCTREE_NBOR_Y_POS] = c->nbors[OCTREE_NBOR_Y_POS];
				nbors[OCTREE_NBOR_Y_NEG] = c->cells[5];
				nbors[OCTREE_NBOR_Z_POS] = c->cells[3];
				nbors[OCTREE_NBOR_Z_NEG] = c->nbors[OCTREE_NBOR_Z_NEG];
				
				if ( nbors[OCTREE_NBOR_X_POS] ) {
					while ( nbors[OCTREE_NBOR_X_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_POS] = nbors[OCTREE_NBOR_X_POS]->cells[0];
					}
					if ( nbors[OCTREE_NBOR_X_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_POS]->nbors[OCTREE_NBOR_X_NEG] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Y_POS] ) {
					while ( nbors[OCTREE_NBOR_Y_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_POS] = nbors[OCTREE_NBOR_Y_POS]->cells[5];
					}
					if ( nbors[OCTREE_NBOR_Y_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_POS]->nbors[OCTREE_NBOR_Y_NEG] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Z_NEG] ) {
					while ( nbors[OCTREE_NBOR_Z_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_NEG] = nbors[OCTREE_NBOR_Z_NEG]->cells[3];
					}
					if ( nbors[OCTREE_NBOR_Z_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_NEG]->nbors[OCTREE_NBOR_Z_POS] = c->cells[i];
					}
				}
				break;
				
			case 2:
				
				nbors[OCTREE_NBOR_X_POS] = c->cells[3];
				nbors[OCTREE_NBOR_X_NEG] = c->nbors[OCTREE_NBOR_X_NEG];
				nbors[OCTREE_NBOR_Y_POS] = c->nbors[OCTREE_NBOR_Y_POS];
				nbors[OCTREE_NBOR_Y_NEG] = c->cells[6];
				nbors[OCTREE_NBOR_Z_POS] = c->nbors[OCTREE_NBOR_Z_POS];
				nbors[OCTREE_NBOR_Z_NEG] = c->cells[0];
				
				if ( nbors[OCTREE_NBOR_X_NEG] ) {
					while ( nbors[OCTREE_NBOR_X_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_NEG] = nbors[OCTREE_NBOR_X_NEG]->cells[3];
					}
					if ( nbors[OCTREE_NBOR_X_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_NEG]->nbors[OCTREE_NBOR_X_POS] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Y_POS] ) {
					while ( nbors[OCTREE_NBOR_Y_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_POS] = nbors[OCTREE_NBOR_Y_POS]->cells[6];
					}
					if ( nbors[OCTREE_NBOR_Y_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_POS]->nbors[OCTREE_NBOR_Y_NEG] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Z_POS] ) {
					while ( nbors[OCTREE_NBOR_Z_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_POS] = nbors[OCTREE_NBOR_Z_POS]->cells[0];
					}
					if ( nbors[OCTREE_NBOR_Z_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_POS]->nbors[OCTREE_NBOR_Z_NEG] = c->cells[i];
					}
				}
				
				break;
			
			case 3:
				
				nbors[OCTREE_NBOR_X_POS] = c->nbors[OCTREE_NBOR_X_POS];
				nbors[OCTREE_NBOR_X_NEG] = c->cells[2];
				nbors[OCTREE_NBOR_Y_POS] = c->nbors[OCTREE_NBOR_Y_POS];
				nbors[OCTREE_NBOR_Y_NEG] = c->cells[7];
				nbors[OCTREE_NBOR_Z_POS] = c->nbors[OCTREE_NBOR_Z_POS];
				nbors[OCTREE_NBOR_Z_NEG] = c->cells[1];
				if ( nbors[OCTREE_NBOR_X_POS] ) {
					while ( nbors[OCTREE_NBOR_X_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_POS] = nbors[OCTREE_NBOR_X_POS]->cells[2];
					}
					if ( nbors[OCTREE_NBOR_X_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_POS]->nbors[OCTREE_NBOR_X_NEG] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Y_POS] ) {
					while ( nbors[OCTREE_NBOR_Y_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_POS] = nbors[OCTREE_NBOR_Y_POS]->cells[7];
					}
					if ( nbors[OCTREE_NBOR_Y_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_POS]->nbors[OCTREE_NBOR_Y_NEG] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Z_POS] ) {
					while ( nbors[OCTREE_NBOR_Z_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_POS] = nbors[OCTREE_NBOR_Z_POS]->cells[1];
					}
					if ( nbors[OCTREE_NBOR_Z_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_POS]->nbors[OCTREE_NBOR_Z_NEG] = c->cells[i];
					}
				}
				
				break;
			
			case 4:
				
				nbors[OCTREE_NBOR_X_POS] = c->cells[5];
				nbors[OCTREE_NBOR_X_NEG] = c->nbors[OCTREE_NBOR_X_NEG];
				nbors[OCTREE_NBOR_Y_POS] = c->cells[0];
				nbors[OCTREE_NBOR_Y_NEG] = c->nbors[OCTREE_NBOR_Y_NEG];
				nbors[OCTREE_NBOR_Z_POS] = c->cells[6];
				nbors[OCTREE_NBOR_Z_NEG] = c->nbors[OCTREE_NBOR_Z_NEG];
				if ( nbors[OCTREE_NBOR_X_NEG] ) {
					while ( nbors[OCTREE_NBOR_X_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_NEG] = nbors[OCTREE_NBOR_X_NEG]->cells[5];
					}
					if ( nbors[OCTREE_NBOR_X_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_NEG]->nbors[OCTREE_NBOR_X_POS] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Y_NEG] ) {
					while ( nbors[OCTREE_NBOR_Y_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_NEG] = nbors[OCTREE_NBOR_Y_NEG]->cells[0];
					}
					if ( nbors[OCTREE_NBOR_Y_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_NEG]->nbors[OCTREE_NBOR_Y_POS] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Z_NEG] ) {
					while ( nbors[OCTREE_NBOR_Z_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_NEG] = nbors[OCTREE_NBOR_Z_NEG]->cells[6];
					}
					if ( nbors[OCTREE_NBOR_Z_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_NEG]->nbors[OCTREE_NBOR_Z_POS] = c->cells[i];
					}
				}
				
				break;
			
			case 5:
				
				nbors[OCTREE_NBOR_X_POS] = c->nbors[OCTREE_NBOR_X_POS];
				nbors[OCTREE_NBOR_X_NEG] = c->cells[4];
				nbors[OCTREE_NBOR_Y_POS] = c->cells[1];
				nbors[OCTREE_NBOR_Y_NEG] = c->nbors[OCTREE_NBOR_Y_NEG];
				nbors[OCTREE_NBOR_Z_POS] = c->cells[7];
				nbors[OCTREE_NBOR_Z_NEG] = c->nbors[OCTREE_NBOR_Z_NEG];
				if ( nbors[OCTREE_NBOR_X_POS] ) {
					while ( nbors[OCTREE_NBOR_X_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_POS] = nbors[OCTREE_NBOR_X_POS]->cells[4];
					}
					if ( nbors[OCTREE_NBOR_X_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_POS]->nbors[OCTREE_NBOR_X_NEG] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Y_NEG] ) {
					while ( nbors[OCTREE_NBOR_Y_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_NEG] = nbors[OCTREE_NBOR_Y_NEG]->cells[1];
					}
					if ( nbors[OCTREE_NBOR_Y_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_NEG]->nbors[OCTREE_NBOR_Y_POS] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Z_NEG] ) {
					while ( nbors[OCTREE_NBOR_Z_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_NEG] = nbors[OCTREE_NBOR_Z_NEG]->cells[7];
					}
					if ( nbors[OCTREE_NBOR_Z_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_NEG]->nbors[OCTREE_NBOR_Z_POS] = c->cells[i];
					}
				}
				
				break;
			
			case 6:
				
				nbors[OCTREE_NBOR_X_POS] = c->cells[7];
				nbors[OCTREE_NBOR_X_NEG] = c->nbors[OCTREE_NBOR_X_NEG];
				nbors[OCTREE_NBOR_Y_POS] = c->cells[2];
				nbors[OCTREE_NBOR_Y_NEG] = c->nbors[OCTREE_NBOR_Y_NEG];
				nbors[OCTREE_NBOR_Z_POS] = c->nbors[OCTREE_NBOR_Z_POS];
				nbors[OCTREE_NBOR_Z_NEG] = c->cells[4];
				if ( nbors[OCTREE_NBOR_X_NEG] ) {
					while ( nbors[OCTREE_NBOR_X_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_NEG] = nbors[OCTREE_NBOR_X_NEG]->cells[7];
					}
					if ( nbors[OCTREE_NBOR_X_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_NEG]->nbors[OCTREE_NBOR_X_POS] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Y_NEG] ) {
					while ( nbors[OCTREE_NBOR_Y_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_NEG] = nbors[OCTREE_NBOR_Y_NEG]->cells[2];
					}
					if ( nbors[OCTREE_NBOR_Y_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_NEG]->nbors[OCTREE_NBOR_Y_POS] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Z_POS] ) {
					while ( nbors[OCTREE_NBOR_Z_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_POS] = nbors[OCTREE_NBOR_Z_POS]->cells[4];
					}
					if ( nbors[OCTREE_NBOR_Z_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_POS]->nbors[OCTREE_NBOR_Z_NEG] = c->cells[i];
					}
				}
				
				break;
			
			case 7:
				
				nbors[OCTREE_NBOR_X_POS] = c->nbors[OCTREE_NBOR_X_POS];
				nbors[OCTREE_NBOR_X_NEG] = c->cells[6];
				nbors[OCTREE_NBOR_Y_POS] = c->cells[3];
				nbors[OCTREE_NBOR_Y_NEG] = c->nbors[OCTREE_NBOR_Y_NEG];
				nbors[OCTREE_NBOR_Z_POS] = c->nbors[OCTREE_NBOR_Z_POS];
				nbors[OCTREE_NBOR_Z_NEG] = c->cells[5];
				if ( nbors[OCTREE_NBOR_X_POS] ) {
					while ( nbors[OCTREE_NBOR_X_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_X_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_X_POS] = nbors[OCTREE_NBOR_X_POS]->cells[6];
					}
					if ( nbors[OCTREE_NBOR_X_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_X_POS]->nbors[OCTREE_NBOR_X_NEG] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Y_NEG] ) {
					while ( nbors[OCTREE_NBOR_Y_NEG]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Y_NEG]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Y_NEG] = nbors[OCTREE_NBOR_Y_NEG]->cells[3];
					}
					if ( nbors[OCTREE_NBOR_Y_NEG]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Y_NEG]->nbors[OCTREE_NBOR_Y_POS] = c->cells[i];
					}
				}
				if ( nbors[OCTREE_NBOR_Z_POS] ) {
					while ( nbors[OCTREE_NBOR_Z_POS]->size > c->cells[i]->size &&
								nbors[OCTREE_NBOR_Z_POS]->flags & OCTREE_CELL_SPLIT ) {
						nbors[OCTREE_NBOR_Z_POS] = nbors[OCTREE_NBOR_Z_POS]->cells[5];
					}
					if ( nbors[OCTREE_NBOR_Z_POS]->size == c->cells[i]->size ) {
						nbors[OCTREE_NBOR_Z_POS]->nbors[OCTREE_NBOR_Z_NEG] = c->cells[i];
					}
				}
				
				break;
		} //end switch
	} //end for
} // end assign_neighbors









/**
 * @brief Initialize an octree.
 * @param g octree object to initialize.
 * @param size Size of octree to create. Must be at least 2. Should be a power of base 2 for best results (e.g. 2, 4, 8, 16, 32, etc.).
 * 
 * 
 */
void octree_init( octree *g, const int size ) {
	assert( g );
	assert( size >= 2 );
	
	memset( g, 0, sizeof(*g) );
	
	g->root = _MALLOC(sizeof(*(g->root)));
	memset( g->root, 0, sizeof(*(g->root)));
	
	g->root->flags = OCTREE_CELL_SOLID;
	g->root->size = size;
	//~ g->root->x = 0;
	//~ g->root->y = 0;
	//~ g->root->z = 0;
}




/**
 * @brief Free an octree_cell and all of its sub cells.
 * @param c Cell to start from, freeing self and children recursively.
 * 
 * 
 */
void free_octree_cell( octree_cell *c ) {
	assert( c );
	
	if ( c->flags & OCTREE_CELL_SPLIT )
	for (int i = 0; i < 8; i++) {
		if ( c->cells[i] ) {
			free_octree_cell( c->cells[i] );
		}
	}
	
	_FREE( c );
}




/**
 * @brief Destroy an octree (free cells).
 * @param g octree object to destroy. octree pointer @p g is not freed.
 * @see octree_init
 * @see free_octree_cell
 * 
 */
void octree_destroy( octree *g ) {
	assert( g );
	
	free_octree_cell( g->root );
}





/**
 * @brief "Set" an octree_cell, marking it as empty space within octree.
 * @param c octree_cell object to mark.
 * @see octree_get
 */
void octree_cell_set( octree_cell *c ) {
	if ( c ) {
		if ( !( c->flags & OCTREE_CELL_SPLIT ) ) {
			c->flags &= ~OCTREE_CELL_SOLID;
		} else {
			for ( int i = 0; i < 8; i++ ) {
				octree_cell_set( c->cells[i] );
			}
		}
	}
}



/**
 * @brief Get the nearest cell to given coordinates. No cells are split.
 * @param g octree to search.
 * @param x X position of desired cell.
 * @param y Y position of desired cell.
 * @param z Z position of desired cell.
 * @returns Returns an octree_cell if coordinates are within bounds of octree. Otherwise return null.
 */
octree_cell* octree_get( octree *g, const int x, const int y, const int z ) {
	assert( g );
	
	if ( x < g->root->size && y < g->root->size && z < g->root->size ) {
		
		octree_cell *curr_c = g->root;
		int i;
		int hsize;
		while ( curr_c->flags & OCTREE_CELL_SPLIT ) {
			hsize = curr_c->size >> 1;
			
			i = 0;
			if ( x >= curr_c->x + hsize ) i = 1;
			if ( y >= curr_c->y + hsize ) i += 4;
			if ( z >= curr_c->z + hsize ) i += 2;
			curr_c = curr_c->cells[i];
			
		} // end while
		
		return curr_c;
	}
	return 0;
}





/**
 * @brief Split an octree_cell once (if not already split and size at least 2).
 * @param c The octree_cell to split.
 * @see octree_cell_split_n
 * @see octree_cell_split_to
 */
void octree_cell_split( octree_cell *c ) {
	assert( c );
	
	if ( !( c->flags & OCTREE_CELL_SPLIT ) && c->size > 1 ) {
		
		int s = c->size >> 1;
		for ( int i = 0; i < 8; i++ ) {
			c->cells[i] = _MALLOC( sizeof(*c) );
			memset( c->cells[i], 0, sizeof(*c) );
			c->cells[i]->size = s;
			c->cells[i]->flags = c->flags;
			
			// x axis (n % 2)
			if ( i % 2 == 0 ) {
				c->cells[i]->x = c->x;
			} else {
				c->cells[i]->x = c->x + s;
			}
			// y axis (n % 4) and z axis ( floor(n * 0.5) % 2 )
			if ( i < 4 ) {
				c->cells[i]->y = c->y;
				if ( i < 2 ) {
					c->cells[i]->z = c->z;
				} else {
					c->cells[i]->z = c->z + s;
				}
			} else {
				// i >= 4
				c->cells[i]->y = c->y + s;
				if ( i < 6 ) {
					c->cells[i]->z = c->z;
				} else {
					c->cells[i]->z = c->z + s;
				}
			}
			
		}
		c->flags = OCTREE_CELL_PARENT;
		
		octree_assign_neighbors( c );
	}
}



/**
 * @brief Split an octree_cell @p n number of times. Stops splitting if size is less than 2.
 * @param c octree_cell object to split.
 * @param n Number of times to split octree_cell @p c.
 * @see octree_cell_split
 * @see octree_cell_split_to
 * 
 */
void octree_cell_split_n( octree_cell *c, const int n ) {
	assert( c );
	
	if ( n > 0 && c->size > 1 ) {
		octree_cell_split( c );
		
		if ( n > 1 ) {
		
			for ( int i = 0; i < 8; i++ ) {
				octree_cell_split_n( c->cells[i], n - 1 );
			}
		}
	}
}



/**
 * @brief Split an octree_cell until split cell size matches @p target_size.
 * @param c octree_cell object to begin split from.
 * @param target_size Final size to split cells to.
 * @see octree_cell_split
 * @see octree_cell_split_n
 * 
 */
void octree_cell_split_to( octree_cell *c, const int target_size ) {
	assert( c );
	assert( target_size > 0 );
	
	if ( c->size > target_size ) {
		octree_cell_split( c );
		
		for ( int i = 0; i < 8; i++ ) {
			octree_cell_split_to( c->cells[i], target_size );
		}
	}
}



/**
 * @brief Minimally split octree until cell with exact coordinates is found.
 * @param g The octree object to cut.
 * @param x X position of desired point.
 * @param y Y position of desired point.
 * @param z Z position of desired point.
 * @returns Returns the octree_cell object that resulted.
 */
octree_cell* octree_cut_point( octree *g, const int x, const int y, const int z ) {
	assert( g );
	
	octree_cell *curr_c = g->root;
	int i;
	int s;
	while ( !(curr_c->x == x && curr_c->y == y && curr_c->z == z) ) {
		i = 0;
		s = curr_c->size >> 1;
		if ( !s ) break; // size > 0
		if ( x >= curr_c->x + s ) i = 1;
		if ( y >= curr_c->y + s ) i += 4;
		if ( z >= curr_c->z + s ) i += 2;
		octree_cell_split( curr_c );
		curr_c = curr_c->cells[i];
	}
	return curr_c;
}




// GODOT functions
#ifdef GODOT

/**
 * @brief Initialize an octree_mesh for use with "rendering".
 * @param m octree_mesh object to initialize.
 * @see octree_mesh_destroy
 * @see octree_cell_render
 */
void octree_mesh_init( octree_mesh *m ) {
	assert( m );
	
	api->godot_pool_vector3_array_new( &(m->verts) );
	api->godot_pool_vector2_array_new( &(m->uvs) );
}
/**
 * @brief Destroy an octree_mesh.
 * @param m octree_mesh object to destroy.
 * @see octree_mesh_init
 * @see octree_cell_render
 */
void octree_mesh_destroy( octree_mesh *m ) {
	assert( m );
	
	api->godot_pool_vector3_array_destroy( &(m->verts) );
	api->godot_pool_vector2_array_destroy( &(m->uvs) );
}



/**
 * @brief Render octree_cell as points and UVs into separate octree_mesh objects.
 * @param c octree_cell object to render.
 * @param floors octree_mesh object for floor faces.
 * @param walls octree_mesh object for wall faces.
 * @param ceilings octree_mesh object for ceiling faces.
 * @see octree_mesh_init
 * @see octree_mesh_destroy
 * 
 */
void octree_cell_render( octree_cell *c, octree_mesh *floors, octree_mesh *walls, octree_mesh *ceilings  ) {
	assert( c );
	assert( floors && walls && ceilings );
	
	if ( c->flags & OCTREE_CELL_SPLIT ) {
		for ( int i = 0; i < 8; i++ ) {
			octree_cell_render( c->cells[i], floors, walls, ceilings );
		}

	} else if ( !( c->flags & OCTREE_CELL_SOLID ) ) {
		octree_cell *nbor;
		// check if neighbors are split
		for ( int i = 0; i < 6; i++ ) {
			nbor = c->nbors[i];
			if (nbor && nbor->flags & OCTREE_CELL_SPLIT) {
				octree_cell_split( c );
				for ( int k = 0; k < 8; k++ ) {octree_cell_render( c->cells[k], floors, walls, ceilings );}
				return;
			}
		}
		// render
		godot_vector3 vec3;
		godot_vector2 vec2;
		int size = c->size, x = c->x, y = c->y, z = c->z;
		// build walls to cover solid neighbors (or empty neighbors), or draw nothing
		nbor = c->nbors[OCTREE_NBOR_X_POS];
		if ( !nbor || nbor->flags & OCTREE_CELL_SOLID ) {
			GD_PV3A_APPEND( &(walls->verts), &vec3, x+size, y, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x+size, y + size, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x+size, y, z + size )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			
			GD_PV3A_APPEND( &(walls->verts), &vec3, x+size, y, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x+size, y + size, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x+size, y + size, z + size )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, size )
		}
		nbor = c->nbors[OCTREE_NBOR_X_NEG];
		if ( !nbor || nbor->flags & OCTREE_CELL_SOLID ) {
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y + size, z )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y + size, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y + size, z )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, size )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			
			
		}
		// box below
		nbor = c->nbors[OCTREE_NBOR_Y_POS];
		if ( !nbor || nbor->flags & OCTREE_CELL_SOLID ) {
			GD_PV3A_APPEND( &(floors->verts), &vec3, x, y, z )
			GD_PV3A_APPEND( &(floors->verts), &vec3, x + size, y, z )
			GD_PV3A_APPEND( &(floors->verts), &vec3, x, y, z + size )
			
			GD_PV2A_APPEND( &(floors->uvs), &vec2, 0, 0 )
			GD_PV2A_APPEND( &(floors->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(floors->uvs), &vec2, 0, size )
			
			GD_PV3A_APPEND( &(floors->verts), &vec3, x + size, y, z )
			GD_PV3A_APPEND( &(floors->verts), &vec3, x + size, y, z + size )
			GD_PV3A_APPEND( &(floors->verts), &vec3, x, y, z + size )
			
			GD_PV2A_APPEND( &(floors->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(floors->uvs), &vec2, size, size )
			GD_PV2A_APPEND( &(floors->uvs), &vec2, 0, size )
			
			
		}
		// box above
		nbor = c->nbors[OCTREE_NBOR_Y_NEG];
		if ( !nbor || nbor->flags & OCTREE_CELL_SOLID ) {
			GD_PV3A_APPEND( &(ceilings->verts), &vec3, x, y + size, z )
			GD_PV3A_APPEND( &(ceilings->verts), &vec3, x, y + size, z + size )
			GD_PV3A_APPEND( &(ceilings->verts), &vec3, x + size, y + size, z )
			
			GD_PV2A_APPEND( &(ceilings->uvs), &vec2, 0, 0 )
			GD_PV2A_APPEND( &(ceilings->uvs), &vec2, 0, size )
			GD_PV2A_APPEND( &(ceilings->uvs), &vec2, size, 0 )
			
			GD_PV3A_APPEND( &(ceilings->verts), &vec3, x + size, y + size, z )
			GD_PV3A_APPEND( &(ceilings->verts), &vec3, x, y + size, z + size )
			GD_PV3A_APPEND( &(ceilings->verts), &vec3, x + size, y + size, z + size )
			
			GD_PV2A_APPEND( &(ceilings->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(ceilings->uvs), &vec2, 0, size )
			GD_PV2A_APPEND( &(ceilings->uvs), &vec2, size, size )
			
			
		}
		nbor = c->nbors[OCTREE_NBOR_Z_POS];
		if ( !nbor || nbor->flags & OCTREE_CELL_SOLID ) {
			GD_PV3A_APPEND( &(walls->verts), &vec3, x + size, y, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y + size, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y, z + size )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, 0 )
			
			GD_PV3A_APPEND( &(walls->verts), &vec3, x + size, y, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x + size, y + size, z + size )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y + size, z + size )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, size )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			
			
			
		}
		nbor = c->nbors[OCTREE_NBOR_Z_NEG];
		if ( !nbor || nbor->flags & OCTREE_CELL_SOLID ) {
			GD_PV3A_APPEND( &(walls->verts), &vec3, x + size, y, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y + size, z )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			
			GD_PV3A_APPEND( &(walls->verts), &vec3, x + size, y, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x, y + size, z )
			GD_PV3A_APPEND( &(walls->verts), &vec3, x + size, y + size, z )
			
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, 0 )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, 0, size )
			GD_PV2A_APPEND( &(walls->uvs), &vec2, size, size )
			
			
		}
		
	}
} // end octree_cell_render

// end ifdef GODOT
#endif


