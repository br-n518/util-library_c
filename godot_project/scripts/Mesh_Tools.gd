
const DEFAULT_UV = [Vector2(0,0), Vector2(1,0),
				Vector2(1,1), Vector2(0,1)] #clockwise
const CENTER_UV_POINT = Vector2(0.5,0.5)
# UV list for specific generated mesh (triangle fan)
const TRIFAN_UV = [DEFAULT_UV[0], DEFAULT_UV[1], CENTER_UV_POINT,
					DEFAULT_UV[1], DEFAULT_UV[2], CENTER_UV_POINT,
					DEFAULT_UV[2], DEFAULT_UV[3], CENTER_UV_POINT,
					DEFAULT_UV[3], DEFAULT_UV[0], CENTER_UV_POINT]
const TRI_UV = [DEFAULT_UV[0], DEFAULT_UV[1], DEFAULT_UV[2],
				DEFAULT_UV[2], DEFAULT_UV[3], DEFAULT_UV[0]]

static func render_mesh(verts:Array, uv_list:Array, material:Material, smooth:bool) -> ArrayMesh:
	var surftool = SurfaceTool.new()
	surftool.begin(Mesh.PRIMITIVE_TRIANGLES)
	var uv_len = len(uv_list)
	for i in range(len(verts)):
		surftool.add_smooth_group(smooth)
		surftool.add_uv(uv_list[i%uv_len])
		surftool.add_vertex(verts[i])
	surftool.generate_normals()
	surftool.set_material(material)
	return surftool.commit()

