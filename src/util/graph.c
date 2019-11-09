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
#include "graph.h"

/**
 * @brief Create a new graph_node with given data pointer.
 * @param data Data to be stored in graph_node.
 * @returns Returns an allocated graph_node.
 * @see graph_node_destroy
 * @see graph_node_destroy_all
 * 
 * 
 */
graph_node* graph_node_create( void *data ) {
	graph_node *ret = _MALLOC( sizeof(graph_node) );
	ret->nbors = NULL;
	ret->data = data;
	return ret;
}


/**
 * @brief Destroy a single graph_node and remove it from graph.
 * @param g graph_node to free.
 * @returns Returns the data pointer stored by destroyed graph_node.
 * @see graph_node_destroy_all
 * 
 */
void* graph_node_destroy( graph_node *g ) {
	assert( g );
	
	graph_node_unlink_all( g );
	g->nbors = NULL;
	void *data = g->data;
	_FREE( g );
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
	_FREE( g );
	return visited;
}

/**
 * @brief Destroy graph_node and all connected graph_nodes.
 * @param g Any node in graph network to be destroyed.
 * @param free_func Function used to free data pointers on nodes.
 * @see graph_node_destroy
 * 
 * 
 */
void graph_node_destroy_all( graph_node *g, void (*free_func)(void*) ) {
	assert( g );
	
	node_t *v = _graph_node_destroy_all( g, free_func, NULL );
	node_free_chain( v );
}



/**
 * @brief Link two graph_nodes together, making them neighbors of each other.
 * @param a A graph_node object
 * @param b Another graph_node object.
 * @see graph_node_unlink
 * @see graph_node_unlink_all
 * 
 */
void graph_node_link( graph_node *a, graph_node *b ) {
	if ( ! node_has( a->nbors, b ) ) {
		node_push_front( &(a->nbors), b );
	}
	if ( ! node_has( b->nbors, a ) ) {
		node_push_front( &(b->nbors), a );
	}
}

/**
 * @brief 
 * @param a 
 * @param b 
 * @see graph_node_link
 * @see graph_node_unlink_all
 * 
 */
void graph_node_unlink( graph_node *a, graph_node *b ) {
	node_remove( &(a->nbors), b );
	node_remove( &(b->nbors), a );
}

/**
 * @brief Unlink a node from all of its connected neighbors.
 * @param g The graph_node object to be "orphaned".
 * @see graph_node_link
 * @see graph_node_unlink
 * 
 */
void graph_node_unlink_all( graph_node *g ) {
	assert( g );
	
	while ( g->nbors ) {
		graph_node_unlink( g->nbors->data, g );
	}
}







/**
 * @brief Get count of neighbors for given graph_node.
 * @param g The node to check.
 * @returns Returns the number of connected neighbors.
 * 
 * 
 */
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

/**
 * @brief Check if a graph_node has a connected path to another graph_node.
 * @param a Starting point.
 * @param b Ending point.
 * @returns Returns 1 if a path was found (OR if @p a and @p b are identical). Returns zero for no path found.
 * 
 * 
 */
int graph_node_has_path( graph_node *a, graph_node *b ) {
	assert( a );
	assert( b );
	
	if ( a == b ) {
		return 1;
	}
	return _graph_node_find_path( a, b, NULL );
}





