extends Spatial

const Mesh_Tools = preload("res://scripts/Mesh_Tools.gd")
var gdn:GDNative

var heights:PoolByteArray
var tiles:Array
var map_size:int
var map_seed:int
var map_roughness:int



func _enter_tree():
	gdn = GDNative.new()
	gdn.library = preload("res://lib/libpcg.tres")






func create_tile(x:int, z:int, size:int) -> MeshInstance:
	var ret = MeshInstance.new()
	
	var verts:PoolVector3Array = [
			Vector3(x * size, heights[(z*(map_size+1)) + x], z * size),
			Vector3((x+1) * size, heights[(z*(map_size+1)) + (x+1)], z * size),
			Vector3((x+1) * size, heights[((z+1)*(map_size+1)) + (x+1)], (z+1) * size),
			Vector3(x * size, heights[(z*(map_size+1)) + x], z * size),
			Vector3((x+1) * size, heights[((z+1)*(map_size+1)) + (x+1)], (z+1) * size),
			Vector3(x * size, heights[((z+1)*(map_size+1)) + x], (z+1) * size)
	]
	
	ret.mesh = Mesh_Tools.render_mesh(
			verts,
			[
					Vector2(0,0),
					Vector2(1,0),
					Vector2(1,1),
					Vector2(0,0),
					Vector2(1,1),
					Vector2(0,1)
			],
			preload("res://assets/cobblestone.material"),
			false)
	
	var phys:StaticBody = StaticBody.new()
	#var coll:CollisionShape = CollisionShape.new()
	var sh:ConcavePolygonShape = ConcavePolygonShape.new()
	sh.set_faces(verts)
	
	#coll.shape = sh
	
	phys.shape_owner_add_shape( phys.create_shape_owner( phys ), sh )
	#phys.add_child(coll)
	ret.add_child(phys)
	return ret




# TODO: Allow larger maps by chunking.
# C routine builds map, then separates into chunks (by args).
# Then heightmap is built of chunks, with camera range 100 or so.
# Then comes stuff like foliage, fauna, and dungeon entrances.
# Water?

func _ready():
	map_size = 64
	map_seed = 20
	map_roughness = 8
	
# warning-ignore:return_value_discarded
	gdn.initialize()
	heights = gdn.call_native("standard_varcall", "dungeon_dsquare", [map_size, map_seed, map_roughness])
# warning-ignore:return_value_discarded
	gdn.terminate()
	
	tiles = []
	var m:MeshInstance
	
	# convert PBA to geometry
	for y in range(map_size):
		for x in range(map_size):
			m = create_tile( x, y, 8 )
			
			tiles.append( m )
			add_child(m)


