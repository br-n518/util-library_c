
#include "grammar.h"

char* create_grammar_str( const char *init_str, node_t *rules, const int iterations ) {
	assert( init_str );
	assert( rules );
	assert( iterations > 0 );
	
	vector_str vs;
	vs_init( &vs );
	vs_set( &vs, init_str );
	
	//const int rule_count = node_count( rules );
	
	int idx;
	node_t *curr;
	rule_t *curr_rule;
	// loop for each iteration
	for ( int i = 0; i < iterations; i++ ) {
		idx = 0;
		curr = rules;
		
		// loop rules
		while ( curr ) {
			// get rule data
			curr_rule = (rule_t*) curr->data;
			// run the rule, adjusting idx
			while ( 1 ) {
				// get next index
				idx = vs_index_of_s_idx( &vs, curr_rule->from, idx );
				
				if ( idx >= 0 ) {
					// replace string
					vs_replace_idx( &vs, curr_rule->from, curr_rule->to, idx );
					
					// forward index by length of new substring
					idx += strlen( curr_rule->to );
				} else {
					// 'from' string not found, break and get next rule
					break;
				}
			}
			
			curr = curr->next;
		}
	}
	
	char *ret = vs_cstr( &vs );
	vs_destroy( &vs );
	
	return ret;
}









