
int test_octree_turtle()
{
	int ret = 1;
	
	octree o;
	octree_init( &o, 64 );
	
	octree_cell_split_to( o.root, 4 );
	
	octree_turtle turtle;
	ot_init( &turtle, octree_get(&o, 16, 16, 16), TURTLE_NORTH );
	
	ot_move_forward( &turtle, 2 );
	
	// TODO check coordinates
	
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

