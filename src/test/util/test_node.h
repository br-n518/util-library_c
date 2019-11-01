
int test_node()
{
	int ret = 1;
	
	int data1 = 40;
	int data2 = 50;
	int data3 = 60;
	
	node_t *head = node_create( &data1 );
	node_insert_after( head, node_create( &data2 ) );
	node_insert_after( head->next, node_create( &data3 ) );
	
	node_t *copy = node_copy_chain( head );
	
	if ( ! assertive("node_copy_chain", copy != head && copy->data == head->data ) )
	{
		ret = 0;
	}
	node_free_chain(copy);
	copy = 0;
	
	if ( ! assertive("node_count", node_count(head) == 3 ))
	{
		ret = 0;
	}
	
	if ( ! assertive("node_insert_after", head->next->next && !( head->next->next->next ) ) )
	{
		ret = 0;
	}
	
	if ( ! assertive("node_has", node_has(head, &data1) &&
			node_has( head, &data2 ) &&
			node_has( head, &data3 ) ))
	{
		ret = 0;
	}
	
	int *p = (int*) node_pop( &head, head->next);
	if ( ! assertive("node_pop", *p == data2 && !( head->next->next ) ) )
	{
		ret = 0;
	}
	
	node_remove( &head, &data3 );
	if ( ! assertive("node_remove", !( head->next ) && !(node_has(head, &data3)) ))
	{
		ret = 0;
	}
	p = (int*) node_pop( &head, head );
		
	if ( ! assertive("node_pop head", !head && p == &data1 && *p == data1 ) )
	{
		ret = 0;
	}
	
	return ret;
}

