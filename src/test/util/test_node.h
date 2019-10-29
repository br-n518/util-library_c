
int test_node() {
	int data1 = 40;
	int data2 = 50;
	int data3 = 60;
	
	node_t *head = node_create( &data1 );
	
	node_insert_after( head, node_create( &data2 ) );
	
	node_insert_after( head->next, node_create( &data3 ) );
	
	// verify tail
	if ( head->next->next && !( head->next->next->next ) ) {
		int *p = (int*) node_pop( &head, head->next );
		// check new tail
		if ( *p == data2 && !( head->next->next ) ) {
			p = (int*) node_pop( &head, head->next );
			
			if ( *p == data3 && !( head->next ) ) {
				
				if ( head->data == &data1 && *(int*) node_pop( &head, head ) == data1 ) {
					
					return 1;
				}
			}
			
		}
		
	}
	
	return 0;
}

