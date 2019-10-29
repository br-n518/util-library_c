/* graph.h - Double-link graph nodes
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
#ifndef GRAPH_H_
#define GRAPH_H_

#include "node.h"

typedef struct graph_node {
	node_t *nbors;
	void *data;
} graph_node;


graph_node* graph_node_create( void *data );
void* graph_node_destroy( graph_node *g );
void graph_node_destroy_all( graph_node *g, void (*free_func)(void*) );

void graph_node_link( graph_node *a, graph_node *b );
void graph_node_unlink( graph_node *a, graph_node *b );
void graph_node_unlink_all( graph_node *g );

int graph_node_neighbor_count( const graph_node *g );

int graph_node_has_path( graph_node *a, graph_node *b );

#endif

