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
#include "split_tiled_map_drawer.h"

#include "../rand/rnd.h"

static rnd_pcg_t tmd_sd_rnd;

typedef struct bsp_node {
	struct bsp_node *left, *right;
	struct rect room;
	int partition;
	char part_vertical;
} bsp_node;




bsp_node* tmd_create_node(struct rect r) {
	bsp_node *node = _MALLOC(sizeof(bsp_node));
	node->room = r;
	node->partition = -1;
	node->left = 0;
	node->right = 0;
	return node;
}

void tmd_free_node(bsp_node *node) {
	if (node != 0) {
		tmd_free_node(node->left);
		tmd_free_node(node->right);
		_FREE(node);
	}
}


int start_x = 0, start_y = 0;
unsigned char start_tile_placed = 0;
void tmd_do_split(tiled_map *map, bsp_node *node);

int tmd_get_start_x() {
	return start_x;
}

int tmd_get_start_y() {
	return start_y;
}

void tmd_split_dungeon(tiled_map *map, unsigned int seed) {
	assert( map );
	
	rnd_pcg_seed( &tmd_sd_rnd, seed );
	
	bsp_node *head = tmd_create_node(create_rect(0, 0, map->width, map->height));
	
	ENEMY_COUNTER = TMD_ENEMY_TILE;
	start_x = 0;
	start_y = 0;
	start_tile_placed = 0;
	tmd_do_split(map, head);
	
	// set exit tile
	bsp_node *curr = head;
	while (curr->right != 0) {
		curr = curr->right;
	}
	//set_tile(map, curr->room.x + (curr->room.w >> 1), curr->room.y + (curr->room.h >> 1), TMD_EXIT_TILE);
	set_tile(map, curr->room.x, curr->room.y, TMD_EXIT_TILE);
	
	tmd_free_node(head);
}

void tmd_partition_room(bsp_node *node, char direction_vertical) {
	// if width less than/equal to half room height (part horizontal)
	node->part_vertical = direction_vertical;
	int p = rnd_pcg_range( &tmd_sd_rnd, -1, 1 );
	if (node->part_vertical == 0) {
		// horizontal
		node->partition = (node->room.h >> 1);
		node->left = tmd_create_node(create_rect(node->room.x+1, node->room.y+1, node->room.w, node->partition + p));
		node->right = tmd_create_node(create_rect(node->room.x+1, node->room.y + node->partition + 1, node->room.w, node->partition - p));
	} else {
		// vertical
		node->partition = (node->room.w >> 1);
		node->left = tmd_create_node(create_rect(node->room.x, node->room.y, node->partition + p, node->room.h));
		node->right = tmd_create_node(create_rect(node->room.x + node->partition, node->room.y, node->partition - p, node->room.h));
	}
}

void tmd_do_split(tiled_map *map, bsp_node *node) {
	// divide
	struct rect r;
	if (node->room.w <= TMD_MIN_ROOM_SIZE || node->room.h <= TMD_MIN_ROOM_SIZE) {
		
		r.x = node->room.x;
		r.w = node->room.w - 1;
		r.y = node->room.y;
		r.h = node->room.h - 1;
		map_draw_rect(map, &r, TMD_ROOM_TILE, 0);
		node->room = r;
		// place start/enemies
		if (start_tile_placed == 1) {
			int i = rnd_pcg_range( &tmd_sd_rnd, 1, 3 ) + 1;
			while ( --i > 0 ) {
				switch (rnd_pcg_range( &tmd_sd_rnd, 0, 3)) {
					case 0:
						set_tile(map, r.x+1, r.y+1, ENEMY_COUNTER);
						break;
					case 1:
						set_tile(map, r.x+r.w-2, r.y+1, ENEMY_COUNTER);
						break;
					case 2:
						set_tile(map, r.x+1, r.y+r.h-2, ENEMY_COUNTER);
						break;
					case 3:
						set_tile(map, r.x+r.w-2, r.y+r.h-2, ENEMY_COUNTER);
						break;
				
				}
			}
			ENEMY_COUNTER++;
		} else {
			start_x = r.x + (r.w>>1);
			start_y = r.y + (r.h>>1);
			start_tile_placed = 1;
		}
		
	} else {
	
		if (node->room.w < node->room.h >> 1) tmd_partition_room(node, 0);
		else if (node->room.h < node->room.w >> 1) tmd_partition_room(node, 1);
		else tmd_partition_room(node, rnd_pcg_next(&tmd_sd_rnd) % 2);
		
		tmd_do_split(map, node->left);
		tmd_do_split(map, node->right);
		
		
		// draw corridors
		if (node->part_vertical == 0) {
			// horizontal split, vertical corridor
			r.x = node->room.x + (node->room.w >> 1);
			r.y = node->room.y + (node->room.h >> 2);
			r.w = 1;
			r.h = node->room.h;
			
		} else {
			r.x = node->room.x + (node->room.w >> 2);
			r.y = node->room.y + (node->room.h >> 1);
			r.w = node->room.w;
			r.h = 1;
		
	
		}
		map_draw_rect(map, &r, TMD_ROOM_TILE, 0);
	}
	
	
}


#ifdef GODOT
godot_variant tmd_get_start(void *data, godot_array *args)
{
	// declare
	godot_variant ret;
	godot_vector2 v;
	// init
	api->godot_vector2_new( &v, tmd_get_start_x(), tmd_get_start_y() ); 
	api->godot_variant_new_vector2( &ret, &v );
	// return
	return ret;
}
#endif


