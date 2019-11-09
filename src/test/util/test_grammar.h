/*
 * This is free and unencumbered software released into the public domain.
 * 
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org>
 */

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
	// "a" : a -> b : "b"
	// "b" : b -> ab : "ab"
	// "ab" : ba -> c : "ab"
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
	// "ab" : a -> b : "bb"
	// "bb" : b -> ab : "abab"
	// "abab" : ba -> c : "acb"
	s = create_grammar_str( "a", rules, 2 );
	if ( ! assertive( "iter 2", strcmp( s, "acb") == 0 ) )
	{
#ifndef NDEBUG
		printf("Value was: '%s'\n", s);
#endif
		ret = 0;
	}
	_FREE(s);
	
	// run grammar procedure (3 iterations)
	// "acb" : a -> b : "bcb"
	// "bcb" : b -> ab : "abcab"
	// "abcab" : ba -> c : "abcab"
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

