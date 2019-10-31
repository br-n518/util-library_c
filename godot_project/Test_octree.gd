extends Spatial

const Mesh_Tools = preload("res://scripts/Mesh_Tools.gd")
var gdn:GDNative

const TRI_UV = [Mesh_Tools.DEFAULT_UV[0], Mesh_Tools.DEFAULT_UV[1], Mesh_Tools.DEFAULT_UV[3],
				Mesh_Tools.DEFAULT_UV[1], Mesh_Tools.DEFAULT_UV[3], Mesh_Tools.DEFAULT_UV[2]]

func _enter_tree():
	gdn = GDNative.new()
	gdn.library = preload("res://lib/libpcg.tres")

func _ready():
	var size:int = 256
	randomize()
	gdn.initialize()

	var a:Array = gdn.call_native("standard_varcall", "dungeon_octree_turtle", [size, 4])

	gdn.terminate()

	var mat = preload("res://assets/inner_roof.material")
	var test:MeshInstance = MeshInstance.new()
	test.mesh = Mesh_Tools.render_mesh(a[4], a[5], mat, false)
	add_child(test)

	mat = preload("res://assets/stone_wall.material")
	test = MeshInstance.new()
	test.mesh = Mesh_Tools.render_mesh(a[0] + a[2], a[1] + a[3], mat, false)
	add_child(test)

	$Camera.translation = Vector3(size >>1, size - 1, size >>1)

# phys_mesh: a[0] + a[2] + a[4]
