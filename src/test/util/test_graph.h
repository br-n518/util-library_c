
int test_graph() {
	int x = 1, y = 20, z = 30;
	graph_node *a = graph_node_create( &x ),
			*b = graph_node_create( &y ),
			*c = graph_node_create( &z );
	int ret = 0;
	
	graph_node_link( a, b );
	graph_node_link( b, c );
	
	if ( graph_node_has_path( a, c ) ) {
		ret = 1;
	}
	
	graph_node_destroy( a );
	graph_node_destroy( b );
	graph_node_destroy( c );
	
	// graph_node_destroy_all( a, NULL );
	
	return ret;
}



