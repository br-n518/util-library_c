
int test_octree_turtle()
{
	int ret = 1;
	
	octree o;
	octree_init( &o, 64 );
	
	octree_cell_split_to( o.root, 2 );
	
	octree_turtle turtle;
	ot_init( &turtle, o.root, TURTLE_NORTH );
	
	ot_move_forward( &turtle, 2 );
	
	// TODO check coordinates
	
	ot_destroy( &turtle );
	octree_destroy( &o );
	
	return ret;
}

