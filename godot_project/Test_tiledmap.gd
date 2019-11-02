extends Spatial


var gdn:GDNative
var grid:GridMap

const WIDTH = 32
const HEIGHT = 32

func _enter_tree():
	gdn = GDNative.new()
	gdn.library = preload("res://lib/libpcg.tres")

func _ready():
	gdn.initialize()
	var SEED = 0
	var pba:PoolByteArray = gdn.call_native("standard_varcall", "dungeon_split_tiled_map", [WIDTH, HEIGHT, SEED])
	var start_pos:Vector2 = gdn.call_native("standard_varcall", "tmd_get_start", [])

	get_node("Player").translation = Vector3(start_pos.x*2, 3, start_pos.y*2)

	grid = array_to_grid(pba)
	add_child(grid)

	# add enemies and exit portal
	var i:int = 0
	for y in range(HEIGHT-1):
		for x in range(WIDTH-1):
			var v = pba[i+x]
			if v == 2:
				# place exit
				var ex = preload("res://Exit.tscn").instance()
				ex.translation = Vector3(x*2, 0, y*2)
				add_child(ex)
			elif v >= 5:
				var e = preload("res://enemies/Grub.tscn").instance()
				e.set_script(preload("res://scripts/Enemy.gd"))
				e.translation = Vector3(x*2, 0, y*2)
				add_child(e)
		i += WIDTH

	gdn.terminate()


static func array_to_grid(array:PoolByteArray) -> GridMap:
	var grid = preload("res://GridMap.tscn").instance()
	var v
	var i
	for y in range(1,HEIGHT-1):
		for x in range(1,WIDTH-1):
			i = (WIDTH*y)+x
			v = array[i]
			# if floor tile
			if v >= 1:
				v = 0
			# if empty and bordering a floor tile
			elif v == 0 and (array[i+WIDTH] >= 1 or array[i+1] >= 1 or array[i-WIDTH] >= 1 or array[i-1] >= 1):
				v = 1
			else:
				# don't draw empty space
				continue
			grid.set_cell_item(x, 0, y, v)
		# outer borders
		grid.set_cell_item(y, 0, 0, 1)
		grid.set_cell_item(0, 0, y, 1)
		grid.set_cell_item(y, 0, HEIGHT-1, 1)
	# span width
	for x in range(1, WIDTH-1):
		grid.set_cell_item(WIDTH-1, 0, x, 1)
	return grid
