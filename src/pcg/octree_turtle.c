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
#include "octree_turtle.h"


void ot_init (octree_turtle * t, octree_cell * start_cell, const char start_direction)
{
	assert( t );
	assert( start_cell );
	
	t->current_cell = start_cell;
	octree_cell_set (start_cell);
	t->flags = start_direction & (char) 0x03;
	t->cell_stack = 0;
	t->direction_stack = 0;
}

void ot_destroy (octree_turtle * t)
{
	assert( t );
	
	if ( t->cell_stack )
		node_free_chain (t->cell_stack);
	while (t->direction_stack)
	{
		_FREE (node_pop (&(t->direction_stack), t->direction_stack));
	}
}

void ot_move_down (octree_turtle * t, const char n)
{
	assert (t);
	assert (n > 0);

	octree_cell *nbor = 0;
	for (char i = 0; i < n; i++)
		{
			nbor = t->current_cell->nbors[OCTREE_NBOR_Y_POS];
			if (nbor)
			{
				octree_cell_split (nbor);
				switch (ot_get_direction (t))
				{
					case TURTLE_NORTH:
						octree_cell_set (nbor->cells[4]);
						octree_cell_set (nbor->cells[5]);
						break;
					case TURTLE_EAST:
						octree_cell_set (nbor->cells[5]);
						octree_cell_set (nbor->cells[7]);
						break;
					case TURTLE_SOUTH:
						octree_cell_set (nbor->cells[6]);
						octree_cell_set (nbor->cells[7]);
						break;
					case TURTLE_WEST:
						octree_cell_set (nbor->cells[4]);
						octree_cell_set (nbor->cells[6]);
						break;
					default:
						return;
				}
				nbor = t->current_cell;
				ot_move_forward (t, 1);

				// check if move forward happened
				if (nbor != t->current_cell)
				{
					nbor = t->current_cell->nbors[OCTREE_NBOR_Y_POS];
					if (nbor)
					{
						octree_cell_set (nbor);
						t->current_cell = nbor;
					}
				}
			}
		}
}

void ot_move_forward (octree_turtle * t, const char n)
{
	assert (t);
	assert (n > 0);

	int nbor_index;
	switch (ot_get_direction (t))
	{
		case TURTLE_NORTH:
			nbor_index = OCTREE_NBOR_Z_POS;
			break;
		case TURTLE_EAST:
			nbor_index = OCTREE_NBOR_X_POS;
			break;
		case TURTLE_SOUTH:
			nbor_index = OCTREE_NBOR_Z_NEG;
			break;
		case TURTLE_WEST:
			nbor_index = OCTREE_NBOR_X_NEG;
			break;
		default:
			nbor_index = -1;
			break;
	}
	if (nbor_index >= 0)
	{
		for (char i = 0; i < n; i++)
		{
			if (t->current_cell->nbors[nbor_index])
			{
				t->current_cell = t->current_cell->nbors[nbor_index];
				octree_cell_set (t->current_cell);
			}
			else
			{
				return;
			}
		}
	}
}


void ot_set_direction (octree_turtle * t, const char direction)
{
	assert (t);

	t->flags &= ~((char) 0x03);
	t->flags |= (direction & (char) 0x03);
}


char ot_get_direction (octree_turtle * t)
{
	assert (t);

	return (t->flags & (char) 0x03);
}


void ot_turn_right (octree_turtle * t)
{
	assert (t);

	char d = ot_get_direction (t);
	if (d >= 3)
		d = 0;
	else
		d++;
	ot_set_direction (t, d);
}

void ot_turn_left (octree_turtle * t)
{
	assert (t);

	char d = ot_get_direction (t);
	if (d == 0)
		d = 3;
	else
		d--;
	ot_set_direction (t, d);
}


void ot_push_cell (octree_turtle * t)
{
	assert (t);

	char *v = _MALLOC (sizeof (char));
	*v = ot_get_direction (t);
	node_push_front (&(t->cell_stack), t->current_cell);
	node_push_front (&(t->direction_stack), v);
}

void ot_pop_cell (octree_turtle * t)
{
	assert (t);

	if (t->cell_stack)
	{
		t->current_cell = node_pop (&(t->cell_stack), t->cell_stack);
		char *v = node_pop (&(t->direction_stack), t->direction_stack);
		ot_set_direction (t, *v);
		_FREE (v);
	}
}

void ot_str_routine (octree_turtle * t, const char *s)
{
	assert (t);

	int i = 0;
	for (;;)
	{
		switch (s[i])
		{
			default:
				break;
			case '\0':
				return; //RETURN
			case 'D':
				ot_move_down (t, 1);
				break;
			case 'F':
				ot_move_forward (t, 1);
				break;
			case '[':
				ot_push_cell (t);
				break;
			case ']':
				ot_pop_cell (t);
				break;
			case '+':
				ot_turn_right (t);
				break;
			case '-':
				ot_turn_left (t);
				break;
		}
		i++;
	}
}




