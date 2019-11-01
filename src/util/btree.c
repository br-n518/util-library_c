/* btree.c
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
#include "btree.h"

void bt_init( btree *tree, const int key, void *data ) {
	assert( tree );
	
	memset( tree, 0, sizeof(*tree) );
	tree->key = key;
	tree->data = data;
}

void bt_put( btree *tree, const int key, void *data ) {
	assert( tree );
	
	if ( tree->key == key ) {
		tree->data = data;
	} else {
		if ( key > tree->key ) {
			if ( tree->right ) {
				bt_put( tree->right, key, data );
			} else {
				tree->right = _MALLOC( sizeof( *tree ) );
				bt_init( tree->right, key, data );
			}
		} else {
			if ( tree->left ) {
				bt_put( tree->left, key, data );
			} else {
				tree->left = _MALLOC( sizeof( *tree ) );
				bt_init( tree->left, key, data );
			}
		}
	}
}

void* bt_get_data( btree *tree, const int key ) {
	assert( tree );
	
	btree *t = bt_get_node(tree, key);
	if (t) return (void*) t->data;
	return 0;
}

btree* bt_get_node( btree *tree, const int key ) {
	assert( tree );
	
	if ( tree->key == key ) {
		return tree;
	} else if ( key > tree->key ) {
		if ( tree->right ) {
			return bt_get_node( tree->right, key );
		}
	} else {
		if ( tree->left ) {
			return bt_get_node( tree->left, key );
		}
	}
	
	return 0;
}



void bt_clear_node( btree *tree, void (*free_func) (void*) )
{
	assert( tree );
	
	if ( tree->right ) {
		bt_clear_node( tree->right, free_func );
	}
	if ( tree->left ) {
		bt_clear_node( tree->left, free_func );
	}
	if ( free_func && tree->data )
		free_func( tree->data );
	_FREE( tree );
}

void bt_clear( btree *tree ) {
	assert( tree );
	
	if ( tree->right ) {
		bt_clear_node( tree->right, 0 );
	}
	if ( tree->left ) {
		bt_clear_node( tree->left, 0 );
	}
	//_FREE( tree );
}

void bt_clear_free( btree *tree, void (*free_func) (void*) ) {
	assert( tree );
	assert( free_func );
	
	if ( tree->right ) {
		bt_clear_node( tree->right, free_func );
	}
	if ( tree->left ) {
		bt_clear_node( tree->left, free_func );
	}
	if ( tree->data )
		free_func( tree->data );
	//_FREE( tree );
}

