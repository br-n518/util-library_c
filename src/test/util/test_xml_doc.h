
int test_xml_doc() {
	
	struct xml_doc *doc = xml_doc_open( "test/test.xml", 1 );
	if (assertive( "xml_doc_open", doc!=0 ))
	{
		
		struct xml_node *n = xml_node_create("test");
		
		xml_node_set_attr(n, "asdf", "banana");
		
		xml_node_add_child(doc->root_node, n);
		
		xml_doc_save( doc, "test/result__test.xml" );
		xml_doc_free( doc );
		return 1;
	}
	return 0;
}

