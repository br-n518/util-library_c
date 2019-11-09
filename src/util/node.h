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
#ifndef NODE_UTIL_H_
#define NODE_UTIL_H_

#include <assert.h>

#include "../alloc.h"

/**
 * @brief Linear linked list node.
 * 
 * 
 */
typedef struct node_t {
	void *data; /**< Data pointer for this node. */
	struct node_t *next; /**< Pointer to next node in chain. */
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
