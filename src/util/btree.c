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
#include "btree.h"

/**
 * @brief Initialize a btree object with key and data pointer.
 * @param tree btree object to initialize.
 * @param key Integer key for binary node.
 * @param data Data pointer stored by node.
 * 
 * 
 */
void bt_init( btree *tree, const int key, void *data )
{
	assert( tree );
	
	memset( tree, 0, sizeof(*tree) );
	tree->key = key;
	tree->data = data;
}

/**
 * @brief Put a new value @p data at given key position.
 * @param tree btree object to modify.
 * @param key Key of desired node. If key exists the result is overwritten.
 * @param data Data pointer to be stored.
 * @returns Returns the previous data pointer if @p key already exists.
 * 
 */
void* bt_put( btree *tree, const int key, void *data )
{
	assert( tree );
	
	void *ret = 0;
	
	if ( tree->key == key )
	{
		ret = tree->data;
		tree->data = data;
	}
	else if ( key > tree->key )
	{
		if ( tree->right )
		{
			// return result of traversal
			ret = bt_put( tree->right, key, data );
		}
		else
		{
			// create new node
			tree->right = _MALLOC( sizeof( *tree ) );
			bt_init( tree->right, key, data );
		}
	}
	else
	{
		if ( tree->left )
		{
			// return result of traversal
			ret = bt_put( tree->left, key, data );
		}
		else
		{
			// create new node
			tree->left = _MALLOC( sizeof( *tree ) );
			bt_init( tree->left, key, data );
		}
	}
	
	return ret;
}

/**
 * @brief Get data stored by given key.
 * @param tree btree object to search.
 * @param key Integer key to search for.
 * @returns Returns the data found, or zero for no match.
 * @see bt_get_node
 * 
 */
void* bt_get_data( btree *tree, const int key )
{
	assert( tree );
	
	btree *t = bt_get_node(tree, key);
	if (t) return (void*) t->data;
	return 0;
}

/**
 * @brief Get node matching given key.
 * @param tree btree object to search from.
 * @param key Integer key to search for.
 * @returns Returns the btree node with matching key, or zero for no match.
 * @see bt_get_data
 * 
 */
btree* bt_get_node( btree *tree, const int key )
{
	assert( tree );
	
	if ( tree->key == key )
	{
		return tree;
	}
	else if ( key > tree->key )
	{
		if ( tree->right )
		{
			return bt_get_node( tree->right, key );
		}
	}
	else
	{
		if ( tree->left )
		{
			return bt_get_node( tree->left, key );
		}
	}
	
	return 0;
}



// hidden function
void bt_clear_node( btree *tree, void (*free_func) (void*) )
{
	assert( tree );
	
	if ( tree->right )
	{
		bt_clear_node( tree->right, free_func );
	}
	if ( tree->left )
	{
		bt_clear_node( tree->left, free_func );
	}
	if ( free_func && tree->data )
		free_func( tree->data );
	_FREE( tree );
}

/**
 * @brief Free node data, leaving data pointers alone.
 * @param tree btree object to clear (except self).
 * @see bt_clear_free
 * @note The root node @p tree is not freed.
 * 
 */
void bt_clear( btree *tree )
{
	assert( tree );
	
	if ( tree->right )
	{
		bt_clear_node( tree->right, 0 );
	}
	if ( tree->left )
	{
		bt_clear_node( tree->left, 0 );
	}
}

/**
 * @brief Free node data and internal data pointers.
 * @param tree btree object to clear (except self).
 * @param free_func Function to use on data pointers.
 * @see bt_clear
 * @note The root node @p tree is not freed.
 * 
 */
void bt_clear_free( btree *tree, void (*free_func) (void*) )
{
	assert( tree );
	assert( free_func );
	
	if ( tree->right )
	{
		bt_clear_node( tree->right, free_func );
	}
	if ( tree->left )
	{
		bt_clear_node( tree->left, free_func );
	}
	if ( tree->data )
		free_func( tree->data );
}

