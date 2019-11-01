
int test_btree() {
	int ret = 0;
	
	const int key1 = 2;
	const int key2 = 3;
	const int key3 = 1;
	const int key4 = 10;
	
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int data4 = 40;
	
	btree head;
	bt_init( &head, key1, &data1 );
	
	//bt_put( head, key1, &data1 );
	bt_put( &head, key2, &data2 );
	bt_put( &head, key3, &data3 );
	bt_put( &head, key4, &data4 );
	
	if ( bt_get_node(&head, key3)->data == &data3 &&
				bt_get_node(&head, key4)->data == &data4 &&
				bt_get_data(&head, key1) == &data1) {
		
		ret = 1;
	}
	bt_clear( &head );
	
	return ret;
}


