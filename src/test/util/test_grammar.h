
int test_grammar()
{
	int ret = 1;
	node_t *rules = 0;
	
	push_grammar_rule( &rules, "a", "b");
	push_grammar_rule( &rules, "b", "ab" );
	push_grammar_rule( &rules, "ba", "c");
	
	if ( ! assertive("push_grammar_rule", rules && rules->data && ((rule_t*) rules->data) ))
	{
		ret = 0;
	}
	
	char *s = create_grammar_str( "a", rules, 1 );
	if ( ! assertive( "iter 1", strcmp( s, "ab") == 0 ) )
	{
		printf("Value was: '%s'\n", s);
		ret = 0;
	}
	_FREE(s);
	
	s = create_grammar_str( "a", rules, 2 );
	if ( ! assertive( "iter 2", strcmp( s, "aca") == 0 ) )
	{
		printf("Value was: '%s'\n", s);
		ret = 0;
	}
	_FREE(s);
	
	s = create_grammar_str( "a", rules, 3 );
	if ( ! assertive( "iter 3", strcmp( s, "abcab") == 0 ) )
	{
		printf("Value was: '%s'\n", s);
		ret = 0;
	}
	_FREE(s);
	
	destroy_grammar( rules );
	rules = 0;
	
	return ret;
}

