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

btree* bt_alloc() {
	return malloc( sizeof(btree) );
}

void bt_init( btree *tree, const int key, void *data ) {
	assert( tree );
	
	memset( tree, 0, sizeof(btree) );
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
				tree->right = bt_alloc();
				bt_init( tree->right, key, data );
			}
		} else {
			if ( tree->left ) {
				bt_put( tree->left, key, data );
			} else {
				tree->left = bt_alloc();
				bt_init( tree->left, key, data );
			}
		}
	}
}

void* bt_get_data( btree *tree, const int key ) {
	assert( tree );
	
	btree *t = bt_get_node(tree, key);
	if (t) return (void*) t->data;
	return NULL;
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
	
	return NULL;
}

void bt_clear( btree *tree ) {
	assert( tree );
	
	if ( tree->right ) {
		bt_clear( tree->right );
	}
	if ( tree->left ) {
		bt_clear( tree->left );
	}
	free( tree );
}

void bt_clear_free( btree *tree, void (*free_func) (void*) ) {
	assert( tree );
	assert( free_func );
	
	if ( tree->right ) {
		bt_clear_free( tree->right, free_func );
	}
	if ( tree->left ) {
		bt_clear_free( tree->left, free_func );
	}
	free_func( tree->data );
	free( tree );
}

