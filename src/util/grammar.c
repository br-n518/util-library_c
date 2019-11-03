/* grammar.c
 *
 * Copyright (c) 2019 br-n518
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "grammar.h"

// hidden function
rule_t* create_grammar_rule( const char *from, const char *to )
{
	assert( from );
	assert( to );
	
	rule_t *ret = _MALLOC( sizeof(*ret) );
	strncpy( ret->from, from, GRAMMAR_STRING_BUFFER_SIZE );
	strncpy( ret->to, to, GRAMMAR_STRING_BUFFER_SIZE );
	return ret;
}

/**
 * @brief Push a new conversion rule to grammar rule list.
 * @param list List of rule_t objects to push to.
 * @param from String to search for when running grammar.
 * @param to Replacement string for each occurrence of @p from.
 * @see destroy_grammar
 * @see create_grammar_str
 */
void push_grammar_rule( node_t **list, const char *from, const char *to )
{
	assert( list );
	assert( from );
	assert( to );
	
	node_push_back( list, create_grammar_rule( from, to ) );
}



/**
 * @brief Destroy a grammar rule list.
 * @param list rule_t object list to free.
 * @see push_grammar_rule
 * @note User should set node_t head pointer to null afterwards.
 */
void destroy_grammar( node_t *list )
{
	assert( list );
	
	node_free_chain_data( list, _FREE );
}


/**
 * @brief Manipulate @p init_str by given @p rules.
 * @param init_str Initial string for running grammar.
 * @param rules node_t list of rule_t objects for describing grammar.
 * @param iterations Number of times to run entire rule list.
 * @returns Returns an allocated string after running grammar rules.
 * @see push_grammar_rule
 * @see destroy_grammar_str
 * @note Rules are processed in series, not in parallel.
 * @note Use macro _FREE on returned string when finished.
 */
char* create_grammar_str( const char *init_str, node_t *rules, const int iterations )
{
	assert( init_str );
	assert( rules );
	assert( iterations > 0 );
	
	// string buffer
	vector_str vs;
	vs_init( &vs );
	vs_set( &vs, init_str );
	
	// index, length of 'to' string
	int idx, to_len;
	
	// node and rule pointers
	node_t *curr_node;
	rule_t *curr_rule;
	
	// loop for each iteration
	for ( int i = 0; i < iterations; i++ )
	{
		// point to head
		curr_node = rules;
		
		// loop rules
		while ( curr_node )
		{
			// get rule data
			curr_rule = (rule_t*) curr_node->data;
			to_len = strlen( curr_rule->to );
			// get first index
			idx = vs_index_of_s_idx( &vs, curr_rule->from, 0 );
			// run the rule, adjusting idx
			while ( idx >= 0 )
			{
				// replace string
				vs_replace_idx( &vs, curr_rule->from, curr_rule->to, idx );
				// forward index by length of new substring
				idx += to_len;
				// get next
				idx = vs_index_of_s_idx( &vs, curr_rule->from, idx );
			}
			// next rule
			curr_node = curr_node->next;
		}
	}
	
	char *ret = vs_cstr( &vs );
	vs_destroy( &vs );
	
	return ret;
}









