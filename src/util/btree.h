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
#ifndef BTREE_H_
#define BTREE_H_

#include <assert.h>
#include <string.h>

#include "../alloc.h"

typedef struct btree {
	struct btree *left, *right;
	void *data;
	int key;
} btree;

#ifdef __cplusplus
extern "C" {
#endif

void bt_init(btree*, const int key, void *data);


void* bt_put(btree *t, const int key, void *data);

void* bt_get_data(btree *t, const int key);
btree* bt_get_node(btree *t, const int key);

void bt_clear(btree*); // free tree nodes
void bt_clear_free(btree*, void (*free_func) (void*)); // tree nodes plus free_func for data



#ifdef __cplusplus
}
#endif



#endif
