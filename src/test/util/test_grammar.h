
int test_grammar()
{
	int ret = 1;
	node_t *rules = 0;
	
	push_grammar_rule( &rules, "a", "b");
	push_grammar_rule( &rules, "b", "ab" );
	push_grammar_rule( &rules, "ba", "c");
	
	// check rules
	if ( ! assertive("push_grammar_rule", rules && rules->data && ((rule_t*) rules->data)->from[0] == 'a' && node_count(rules) == 3 ))
	{
		ret = 0;
	}
	
	// run grammar procedure (1 iteration)
	char *s = create_grammar_str( "a", rules, 1 );
	if ( ! assertive( "iter 1", strcmp( s, "ab") == 0 ) )
	{
#ifndef NDEBUG
		printf("Value was: '%s'\n", s);
#endif
		ret = 0;
	}
	_FREE(s);
	
	// run grammar procedure (2 iterations)
	s = create_grammar_str( "a", rules, 2 );
	if ( ! assertive( "iter 2", strcmp( s, "aca") == 0 ) )
	{
#ifndef NDEBUG
		printf("Value was: '%s'\n", s);
#endif
		ret = 0;
	}
	_FREE(s);
	
	// run grammar procedure (3 iterations)
	s = create_grammar_str( "a", rules, 3 );
	if ( ! assertive( "iter 3", strcmp( s, "abcab") == 0 ) )
	{
#ifndef NDEBUG
		printf("Value was: '%s'\n", s);
#endif
		ret = 0;
	}
	_FREE(s);
	
	// free memory
	destroy_grammar( rules );
	rules = 0;
	
	return ret;
}

