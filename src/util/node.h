/* node.h
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
#ifndef NODE_UTIL_H_
#define NODE_UTIL_H_

#include <assert.h>

#ifdef GODOT
#	include "../gdnative/godot_sub_native.h"
#	define _MALLOC api->godot_alloc
#	define _FREE api->godot_free
#else
#	include <stdlib.h>
#	define _MALLOC malloc
#	define _FREE free
#endif

typedef struct node_t {
	void *data;
	struct node_t *next;
} node_t;



#ifdef __cplusplus
extern "C" {
#endif

node_t* node_create( void *data );

void node_free_chain( node_t *node );
node_t* node_copy_chain( node_t *head );
void node_free_chain_data( node_t *node, void (*data_free_func)(void*) );

// returns data removed, sets head to NULL if last node popped
void* node_pop( node_t **head, node_t *node );

/**
 * @brief Insert single node (or node chain) after the given node @p base
 */
void node_insert_after( node_t *base, node_t *node );

// front is faster
void node_push_back( node_t **head, void *data );
void node_push_front( node_t **head, void *data );

int node_has( node_t *node, const void *data );

void node_remove( node_t **head, const void *data );

int node_count( node_t *head );

#ifdef __cplusplus
}
#endif


#endif
