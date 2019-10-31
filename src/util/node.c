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



node_t * node_create( void *data ) {
	node_t *ret = _MALLOC(sizeof(node_t));
	ret->next = 0;
	ret->data = data;
	return ret;
}



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
	_FREE(node);
}

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

void* node_pop( node_t **head, node_t *node ) {
	assert( head );
	assert( (*head) );
	assert( node );
	
	node_t *curr;
	void *ret = node->data;
	//node->data = 0;
	if ( (*head) == node ) {
		(*head) = (*head)->next;
	} else {
		curr = (*head);
		while ( curr->next && curr->next != node ) {
			curr = curr->next;
		}
		if ( curr->next == node ) {
			curr->next = node->next;
		}
	}
	
	_FREE(node);
	return ret;
}

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

int node_has( node_t *node, const void *data ) {
	while ( node ) {
		if ( node->data == data ) return 1;
		node = node->next;
	}
	return 0;
}

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







