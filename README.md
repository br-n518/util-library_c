
# util_lib

[License](LICENSE)

### src
- **alloc.h**: allows toggling malloc and godot_alloc.
- **godot.c**: interfaces the pcg tools to GDNative.
- **nativescript_ini_doc.c**: NativeScript interface for ini_doc.

### util
- **node.h**: Linear linked list.
- **btree.h**: Binary sort tree.
- **grammar.h**: Grammar string evolver.
- **graph.h**: Double-linked graph nodes.
- **hash.h**: Hash table for storing data by string key.
- **strbuff.h**: Continuous string buffer.
- **vector_str.h**: Vector string for mutability.  
&nbsp;

- **ini_doc.h**: INI file reader/writer.
- **xml_doc.h**: XML file reader/writer.
	- Comments are stripped and ignored. ini_doc comments can be at the end of any line.
	- Text elements inside XML nodes are concatenated after stripping  
	leading & trailing whitespace (per block of node-separated text).

### terrain
- **tiled_map.h**: Tiled map (for 2D or flat-ground 3D).
- **heightmap.h**: Heightmap (for 3D terrain).
- **octree.h**: Start with a large cube, then divide to 8 cubes.  
	Repeat the process, creating the octal tree (until size==1).

### pcg
- **split_tiled_map_drawer.h**: Tiled map binary split algorithm.
- **dsquare_hmap.h**: Diamond square over heightmap.
- **octree_turtle.h**: Octree "turtle" drawer.

### rand
- **rand.h**: C++ &lt;random&gt; library wrapper for C.

### gdnative
- Macros and headers to simplify godot_headers usage.
	- **godot_macros.h**: Macros to reduce code when using GDNative API.
	- **godot_sub_native.h**: Include by modules needing GDNative API struct.
	- **godot_native.h**: Define GDNative API struct and init functions.

### GDScript

- **ini_doc.gd**: Stand-alone GDScript version of ini_doc using Dictionary.

# Building

### Requirements

- **gcc** (GNU C Compiler)
- **make**
- **bash** (optional: for test scripts)

On Linux these can be easily installed from repository.  
For Windows, MinGW (*Minimalist GNU for Windows*) includes gcc and make.  

Note that the code is tailored for Linux, and getting the library to export to working DLL is currently WIP.

The **godot_headers** are also necessary. They're added to this repository as a submodule,
but they don't download automatically. Use duckduckgo.com for info on git submodule,
or you can download them manually by following the submodule link on github.

### stdlib.h malloc

    make

### Godot build (GDNative)

    make godot

### Godot test

    make godot
    make deploy

### ini_doc NativeScript Class

    make ns_ini_doc
    cp bin/ini_doc.so godot_project/lib/

Now create `ini_doc.tres` to point to `ini_doc.so`/`ini_doc.dll`  
and create `ini_doc.gdns` for referencing the "ini_doc" class name.

##### Example usage:

    const INI_DOC = preload("res://lib/ini_doc.gdns")
    
    var doc = INI_DOC.new()
    doc.set("section1", "key1", "value1")
    doc.set_global("key2", "value2")
    doc.save("../file.ini")

Currently ini_doc class does not support Godot path prefixes (res, user, and sys://).

##### ns_ini_doc functions

    set( section, key, value )
    get( section, key ) -> String
    
    set_global( key, value )
    get_global( key ) -> String
    
    open( filename )
    save( filename )
    parse( file_data )
    to_string() -> String

