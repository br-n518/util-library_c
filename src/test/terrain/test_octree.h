
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
