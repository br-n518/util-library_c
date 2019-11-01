/* btree.h
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


void bt_put(btree *t, const int key, void *data);

void* bt_get_data(btree *t, const int key);
btree* bt_get_node(btree *t, const int key);

void bt_clear(btree*); // free tree nodes
void bt_clear_free(btree*, void (*free_func) (void*)); // tree nodes plus free_func for data



#ifdef __cplusplus
}
#endif



#endif
