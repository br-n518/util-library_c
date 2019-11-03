/* node.c
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
#include "node.h"



/**
 * @brief 
 * @param data 
 * @returns 
 * 
 * 
 */
node_t * node_create( void *data ) {
	node_t *ret = _MALLOC(sizeof(*ret));
	ret->next = 0;
	ret->data = data;
	return ret;
}



/**
 * @brief 
 * @param node 
 * 
 * 
 */
void node_free_chain( node_t *node ) {
	assert( node );
	
	node_t *next = node->next;
	while ( next ) {
		_FREE( node );
		node = next;
		next = next->next;
	}
	_FREE(node);
}

/**
 * @brief 
 * @param node 
 * @param data_free_func 
 * 
 * 
 */
void node_free_chain_data( node_t *node, void (*data_free_func)(void*) ) {
	assert( node );
	assert( data_free_func );
	
	node_t *next = node->next;
	while ( next ) {
		if ( node->data )
			data_free_func( node->data );
		_FREE( node );
		node = next;
		next = next->next;
	}
	if ( node->data )
		data_free_func( node->data );
	_FREE(node);
}

/**
 * @brief 
 * @param head 
 * @returns 
 * 
 * 
 */
node_t* node_copy_chain( node_t *head ) {
	assert( head );
	
	node_t *ret = node_create( head->data );
	node_t *curr = head->next;
	node_t *ret_tail = ret;
	while ( curr ) {
		ret_tail->next = node_create( curr->data );
		ret_tail = ret_tail->next;
		curr = curr->next;
	}
	return ret;
}

/**
 * @brief Find and pop the given node @p node from chain.
 * @param head Node chain head pointer.
 * @param node Node to remove. Can be head node.
 * @returns Returns the popped data, or zero for node not found in chain.
 * 
 * 
 */
void* node_pop( node_t **head, node_t *node )
{
	assert( head );
	assert( (*head) );
	assert( node );
	
	void *ret = 0;
	
	// if popping head node
	if ( (*head) == node )
	{
		(*head) = (*head)->next;
	}
	// find node
	else
	{
		node_t *curr = (*head);
		while ( curr->next && curr->next != node )
		{
			curr = curr->next;
		}
		if ( curr->next == node )
		{
			ret = node->data;
			curr->next = node->next;
			_FREE(node);
		}
	}
	
	return ret;
}

/**
 * @brief Insert single node (or node chain) after the given node @p base.
 * @param base Base node for insertion.
 * @param node Node to insert after @p base. May be a single node or chain of nodes.
 * 
 * 
 */
void node_insert_after( node_t *base, node_t *node ) {
	assert( base );
	assert( node );
	
	// get last node of node-chain
	node_t *tail = node;
	while ( tail->next ) {
		tail = tail->next;
	}
	// connect tail node (maybe 0)
	tail->next = base->next;
	// connect head
	base->next = node;
}

/**
 * @brief Push data to the end (tail) of a node chain.
 * @param head Node chain head pointer.
 * @param data Data pointer.
 * 
 * 
 */
void node_push_back( node_t **head, void *data ) {
	assert( head );
	assert( data );
	
	if ( *head ) {
		node_t *curr = *head;
		while ( curr->next ) curr = curr->next;
		curr->next = node_create( data );
	} else {
		(*head) = node_create( data );
	}
}

/**
 * @brief Push data to the beginning (head) of a node chain.
 * @param head Node chain head pointer.
 * @param data Data pointer.
 * 
 * 
 */
void node_push_front( node_t **head, void *data ) {
	assert( head );
	assert( data );
	
	if ( (*head) ) {
		node_t *node = node_create( data );
		node->next = (*head);
		(*head) = node;
	} else {
		(*head) = node_create( data );
	}
}

/**
 * @brief Check if a node chain has a data pointer.
 * @param node Node chain head to search.
 * @param data Data pointer value to search for.
 * @returns Returns non-zero for data found. Otherwise return zero.
 * 
 * 
 */
int node_has( node_t *node, const void *data ) {
	while ( node ) {
		if ( node->data == data ) return 1;
		node = node->next;
	}
	return 0;
}

/**
 * @brief Remove a node by data pointer.
 * @param head Head of node chain to search.
 * @param data The data pointer to match, then remove node.
 * 
 * 
 */
void node_remove( node_t **head, const void *data ) {
	node_t *node = *head, *prev = 0;
	while ( node ) {
		if ( node->data == data ) {
			// found the node
			if (prev) {
				// node is NOT first in list (head)
				prev->next = node->next;
				_FREE( node );
			} else {
				// no previous, we're on the head node
				assert( node == *head );
				//node = *head;
				*head = node->next;
				_FREE( node );
			}
			break;
		}
		prev = node;
		node = node->next;
	}
}

/**
 * @brief Count number of nodes in a chain.
 * @param head Node chain to count.
 * @returns Returns 0 for empty chain, or 1 for each node in chain.
 * 
 * 
 */
int node_count( node_t *head ) {
	if ( head ) {
		int ret = 1; // 1 for head node
		while ( head->next ) { // +1 more node
			head = head->next;
			ret++;
		}
		return ret;
	}
	return 0;
}







