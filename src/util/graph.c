/* graph.c
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
#include "graph.h"

graph_node* graph_node_create( void *data ) {
	graph_node *ret = malloc( sizeof(graph_node) );
	ret->nbors = NULL;
	ret->data = data;
	return ret;
}


void* graph_node_destroy( graph_node *g ) {
	assert( g );
	
	graph_node_unlink_all( g );
	g->nbors = NULL;
	void *data = g->data;
	free( g );
	return data;
}


node_t* _graph_node_destroy_all( graph_node *g, void (*free_func)(void*), node_t *visited ) {
	node_t *curr = g->nbors;
	node_push_front( &visited, g );
	while ( curr ) {
		if ( ! node_has( visited, curr->data ) ) {
			visited = _graph_node_destroy_all( curr->data, free_func, visited );
		}
		curr = curr->next;
	}
	node_free_chain( g->nbors );
	g->nbors = NULL;
	if ( free_func ) {
		free_func( g->data );
	}
	free( g );
	return visited;
}

void graph_node_destroy_all( graph_node *g, void (*free_func)(void*) ) {
	assert( g );
	
	node_t *v = _graph_node_destroy_all( g, free_func, NULL );
	node_free_chain( v );
}



void graph_node_link( graph_node *a, graph_node *b ) {
	if ( ! node_has( a->nbors, b ) ) {
		node_push_front( &(a->nbors), b );
	}
	if ( ! node_has( b->nbors, a ) ) {
		node_push_front( &(b->nbors), a );
	}
}

void graph_node_unlink( graph_node *a, graph_node *b ) {
	node_remove( &(a->nbors), b );
	node_remove( &(b->nbors), a );
}

void graph_node_unlink_all( graph_node *g ) {
	assert( g );
	
	while ( g->nbors ) {
		graph_node_unlink( g->nbors->data, g );
	}
}







int graph_node_neighbor_count( const graph_node *g ) {
	return node_count( g->nbors );
}






int _graph_node_find_path( graph_node *a, graph_node *b, node_t *visited ) {
	assert( a );
	assert( b );
	
	if ( ! node_has( visited, a ) ) {
		// memory freed on last recursion
		node_push_front( &visited, a );
		
		node_t *node = a->nbors;
		while ( node ) {
			if ( node->data == b ) {
				// free memory (once)
				node_free_chain( visited );
				return 1;
			} else {
				if ( _graph_node_find_path( node->data, b, visited ) ) return 1;
			}
			node = node->next;
		}
	}
	return 0;
}

int graph_node_has_path( graph_node *a, graph_node *b ) {
	assert( a );
	assert( b );
	
	if ( a == b ) {
		return 1;
	}
	return _graph_node_find_path( a, b, NULL );
}





