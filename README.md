
# util_lib

## src
- **alloc.h** allows toggling malloc and godot_alloc.
- **godot.c** interfaces the pcg tools to GDNative.

### util
- Linear linked list (**node.h**)
- Binary sort tree (**btree.h**)
- Grammar string evolver (**grammar.h**)
- Double-linked graph nodes (**graph.h**)
- Hash table for storing data by string key (**hash.h**)
- Continuous string buffer (**strbuff.h**)
- Vector string for mutability (**vector_str.h**)

- INI file reader/writer (**ini_doc.h**)
- XML file reader/writer (**xml_doc.h**)
	- Comments are stripped and ignored.
	- Text elements inside nodes are concatenated after  
	stripping leading & trailing whitespace (per block of text).

### terrain
- Tiled map (for 2D or flat-ground 3D) (**tiled_map.h**)
- Heightmap (for 3D terrain) (**heightmap.h**)
- Octree (start with a large cube, then divide to 8 cubes.  
	Repeat the process, creating the octal tree) (**octree.h**)

### pcg
- Diamond square over heightmap. (**dsquare_hmap.h**)
- Octree "turtle" drawer. (**octree_turtle.h**)
- Tiled map binary split algorithm. (**split_tiled_map_drawer.h**)

### rand
- C++ &lt;random&gt; library wrapper for C (**rand.h**)

### gdnative
- Macros and headers to simplify godot_headers usage.


