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
#ifndef OCTREE_TURTLE_H_
#define OCTREE_TURTLE_H_

#include <string.h>
#include "../util/node.h"
#include "../util/grammar.h"
#include "../terrain/octree.h"

#include "../alloc.h"

// first two bits (number range)
#define TURTLE_NORTH 0
#define TURTLE_EAST 1
#define TURTLE_SOUTH 2
#define TURTLE_WEST 3

// next two bits (bit flags)
#define TURTLE_DOWN 4
#define TURTLE_UP 8

// 4 bits free (bit 16, 32, 64, and 128)

typedef struct octree_turtle {
	octree_cell *current_cell;
	node_t *cell_stack;
	node_t *direction_stack;
	char flags;
} octree_turtle;

#ifdef __cplusplus
extern "C" {
#endif

void ot_init( octree_turtle *t, octree_cell *start_cell, const char start_direction );
void ot_destroy( octree_turtle *t );

void ot_move_down( octree_turtle *t, const char n );
void ot_move_forward( octree_turtle *t, const char n );

void ot_set_direction( octree_turtle *t, const char direction );

char ot_get_direction( octree_turtle *t );

void ot_turn_right( octree_turtle *t );
void ot_turn_left( octree_turtle *t );

void ot_push_cell( octree_turtle *t );
void ot_pop_cell( octree_turtle *t );

void ot_str_routine( octree_turtle *t, const char *s );

#ifdef __cplusplus
}
#endif



#endif

