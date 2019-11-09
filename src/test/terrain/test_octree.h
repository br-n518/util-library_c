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
int test_octree()
{
	int ret = 0;
	octree head;
	octree_init( &head, 128 ); // size of map, 128 cubed with subdivision (min cell size = 1)
	
	// split 4 times, should have 128[0] 64[1] 32[2] 16[3] 8[4] so tiles are size 8
	octree_cell_split_n( head.root , 4 );
	
	if ( head.root->cells[0]->cells[0]->cells[0]->cells[0] &&
				!( head.root->cells[0]->cells[0]->cells[0]->cells[0]->flags & OCTREE_CELL_SPLIT )) {
		
		// split first cell until child nodes include size 4 nodes (one more split)
		octree_cell_split_to( head.root->cells[0], 4 );
		
		// verify split one level lower (only for head.root->cells[0]...)
		if ( head.root->cells[0]->cells[0]->cells[0]->cells[0]->cells[1] &&
					!( head.root->cells[0]->cells[0]->cells[0]->cells[0]->cells[1]->flags & OCTREE_CELL_SPLIT )) {
			
			ret = 1;
		}
	}
	octree_destroy( &head );
	
	return ret;
}
