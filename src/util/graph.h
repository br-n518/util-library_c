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
#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"
#include "../alloc.h"

typedef struct graph_node {
	node_t *nbors;
	void *data;
} graph_node;


#ifdef __cplusplus
extern "C" {
#endif

graph_node* graph_node_create( void *data );
void* graph_node_destroy( graph_node *g );
void graph_node_destroy_all( graph_node *g, void (*free_func)(void*) );

void graph_node_link( graph_node *a, graph_node *b );
void graph_node_unlink( graph_node *a, graph_node *b );
void graph_node_unlink_all( graph_node *g );

int graph_node_neighbor_count( const graph_node *g );

int graph_node_has_path( graph_node *a, graph_node *b );

#ifdef __cplusplus
}
#endif



#endif

