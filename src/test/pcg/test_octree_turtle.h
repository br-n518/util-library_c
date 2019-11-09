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
int test_octree_turtle()
{
	int ret = 1;
	
	octree o;
	octree_init( &o, 64 );
	
	octree_cell_split_to( o.root, 4 );
	
	octree_turtle turtle;
	ot_init( &turtle, octree_get(&o, 16, 16, 16), TURTLE_NORTH );
	
	ot_move_forward( &turtle, 2 );
	
	octree_cell *cell = octree_get(&o, 16, 16, 16);
	
	if ( ! assertive("ot_move_forward", ! (cell->flags & OCTREE_CELL_SOLID ||
			cell->nbors[OCTREE_NBOR_Z_POS]->flags & OCTREE_CELL_SOLID ||
			cell->nbors[OCTREE_NBOR_Z_POS]->nbors[OCTREE_NBOR_Z_POS]->flags & OCTREE_CELL_SOLID
			) && cell->nbors[OCTREE_NBOR_X_POS]->flags & OCTREE_CELL_SOLID ) )
	{
		ret = 0;
	}
	
	
	ot_destroy( &turtle );
	octree_destroy( &o );
	
	return ret;
}

