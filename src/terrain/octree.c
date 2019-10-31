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
			
		}
	}
} // end assign_neighbors









void octree_init( octree *g, const int size ) {
	assert( g );
	assert( size >= 2 );
	
	memset( g, 0, sizeof(octree) );
	
	g->root = _MALLOC(sizeof(octree_cell));
	memset( g->root, 0, sizeof(octree_cell));
	
	g->root->flags = OCTREE_CELL_SOLID;
	g->root->size = size;
	g->root->x = 0;
	g->root->y = 0;
	g->root->z = 0;
}




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




void octree_destroy( octree *g ) {
	assert( g );
	
	free_octree_cell( g->root );
}





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





void octree_cell_split( octree_cell *c ) {
	assert( c );
	
	if ( !( c->flags & OCTREE_CELL_SPLIT ) && c->size > 1 ) {
		
		int s = c->size >> 1;
		for ( int i = 0; i < 8; i++ ) {
			c->cells[i] = _MALLOC( sizeof(octree_cell) );
			memset( c->cells[i], 0, sizeof(octree_cell) );
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





