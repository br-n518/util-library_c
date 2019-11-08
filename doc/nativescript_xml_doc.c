
#include "gdnative/godot_native.h"

#include "util/xml_doc.h"


typedef struct ns_xml_doc
{
	struct xml_doc *doc;
	struct xml_node *selected_node;
	char case_sensitive;
} ns_xml_doc;


GDCALLINGCONV void* xml_doc_constructor(godot_object *p_instance, void *p_method_data)
{
	ns_xml_doc *data = api->godot_alloc( sizeof( *data ) );
	
	data->doc = xml_doc_create();
	data->selected_node = 0;
	data->case_sensitive = 0;
	
	return data;
}

GDCALLINGCONV void xml_doc_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
	xml_doc_free(p_user_data->doc);
	api->godot_free( p_user_data );
}





/*

// Function args with a value are optional arguments.

// case sensitive search
// disabled by default: always match case-insensitive

use_case_sensitive_search( b:bool=1 )
case_sensitive_enabled( ) -> bool

// NODE SELECTION

select_root( )
select_child( String ) -> bool
select_sibling( String) -> bool (select_parent then select_child, but noting index via pointer matching)
select_parent( ) -> bool
select_xpath( String ) -> bool (can be relative or absolute, can only select nodes, not attributes or any text values.)

select_next_sibling( ) -> bool

find_child( String ) -> bool  (searches from current selected node until node with matching name is found)

get_tag_name( ) -> String
get_children_tag_names() -> PoolStringArray

// ATTRIBUTES

set_attribute_value( String, String )
append_attribute_value( String, String )
get_attribute_value( String ) -> String

set_attributes( Dictionary )
get_attributes( ) -> Dictionary

unset_attribute( String )

// TEXT

set_text( String )
append_text( String )
get_text( ) -> String

// NODE CREATION AND DELETION

create_root_node( String, encoding:String="UTF-8", version:String="1.0" )  (Deletes any XML document contents before creating)
create_child_node( String, idx:int=-1 )
delete_child_node_at( int, connect:bool=0 )  (deletes all child nodes of child by default)
delete_selected_node( connect:bool=0 )  (selects parent, or none if root deleted; deletes all child nodes by default)

// HAS

has_child( String, recursive:bool=0 ) -> bool
has_attribute( String ) -> bool
has_text( String, case_sensitive:bool=1 ) -> bool  (case sensitivity here is separate from global tag matching setting)

// FILE-BASED OPERATIONS

open( fname:String, strict_format:bool=0 )
parse( data:String, strict_format:bool=0 )
save( fname:String, use_xml_header:bool=1 )
to_string( use_xml_header:bool=0 ) -> String

// OTHER

set_encoding( String )
get_encoding( ) -> String

set_version( String )
get_version( ) -> String

get_version_major( ) -> int
get_version_minor( ) -> int






implement filepath conversion via Godot
maybe there's a small function to find, but need Godot's info because
game developer is able to choose directory, not to mention Android vs. anything else paths. therefore necessary

Need Godot to convert res:// sys:// and user:// for the base file IO objects
Then the nativescript wrapper doesn't worry about it, just send filepath.
Going to need cpp macro #ifdef GODOT
If Godot then translate the file path with Godot
Otherwise use current behavior (stdio.h handles everything)

*/




godot_variant  ns_xml_doc_use_case_sensitive_search( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *data = (ns_xml_doc*) p_user_data;
	
	godot_bool b = 1;
	
	if ( p_num_args >= 1 )
	{
		b = api->godot_variant_as_bool(p_args[0]);
	}
	
	data->case_sensitive = b;
	
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_case_sensitive_enabled( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *data = (ns_xml_doc*) p_user_data;
	
	godot_variant ret_var;
	api->godot_variant_new_bool( &ret_var, (godot_bool) data->case_sensitive );
	
	return ret_var;
}

godot_variant  ns_xml_doc_select_root( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *data = (ns_xml_doc*) p_user_data;
	
	data->selected_node = data->doc->root_node;
	
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_select_child( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_select_sibling( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_select_parent( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_select_xpath( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_select_next_sibling( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_find_child( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_get_tag_name( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_string(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_get_children_tag_names( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_pool_string_array(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_set_attribute_value( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_append_attribute_value( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_get_attribute_value( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_string(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_set_attributes( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_get_attributes( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_dictionary(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_unset_attribute( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_set_text( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_append_text( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
	
}

godot_variant  ns_xml_doc_get_text( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_string(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_create_root_node( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_create_child_node( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_delete_child_node_at( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_delete_selected_node( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_has_child( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_has_attribute( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_has_text( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}





godot_variant ns_xml_doc_open( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		godot_bool use_strict_formatting = 0;
		if ( p_num_args >= 2 )
		{
			api->godot_variant_as_bool(p_args[1]);
		}
		
		if ( doc )
		{
			xml_doc_free(doc);
		}
		
		// call xml_doc_load
		doc = xml_doc_open( api->godot_char_string_get_data(&cs_fname), use_strict_formatting );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}


godot_variant ns_xml_doc_save( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		godot_bool use_xml_header = 1;
		if ( p_num_args >= 2 )
		{
			use_xml_header = api->godot_variant_as_bool(p_args[1]);
		}
		if ( use_xml_header )
		{
			xml_doc_save( doc,
					api->godot_char_string_get_data(&cs_fname) );
		}
		else
		{
			xml_doc_save_sans_prolog( doc,
					api->godot_char_string_get_data(&cs_fname) );
		}
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
	}
	GD_RETURN_NIL()
}


godot_variant ns_xml_doc_parse( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string data_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_data = api->godot_string_ascii(&data_str);
		// delete string
		api->godot_string_destroy(&data_str);
		
		xml_doc_parse( doc, api->godot_char_string_get_data(&cs_data), api->godot_char_string_length(&cs_data) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_data );
	}
	GD_RETURN_NIL()
}





godot_variant  ns_xml_doc_to_string( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_string ret = 0;
	
	godot_bool use_xml_header = 0;
	if ( p_num_args >= 1 )
	{
		// get args
		use_xml_header = api->godot_variant_as_bool(p_args[0]);
		
	}
	// convert key arg
	godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
	api->godot_string_destroy(&fname_str);
	
	ret = xml_doc_to_string( doc, use_xml_header );
	
	// cleanup
	api->godot_char_string_destroy( &cs_fname );
	
	godot_variant ret_var;
	api->godot_variant_new_stringl(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_set_encoding( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_get_encoding( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_string(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_set_version( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	GD_RETURN_NIL()
}

godot_variant  ns_xml_doc_get_version( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_string(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_get_version_major( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{
	
	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_int(&ret_var, ret);
	
	return ret_var;
}

godot_variant  ns_xml_doc_get_version_minor( godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args )
{

	ns_xml_doc *doc = (ns_xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_int(&ret_var, ret);
	
	return ret_var;
}





void GDN_EXPORT godot_nativescript_init( void *p_handle )
{
	godot_instance_create_func create = { NULL, NULL, NULL };
	create.create_func = &ns_xml_doc_constructor;

	godot_instance_destroy_func destroy = { NULL, NULL, NULL };
	destroy.destroy_func = &ns_xml_doc_destructor;

	nativescript_api->godot_nativescript_register_class(p_handle, "xml_doc", "Node", create, destroy);


	godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };
	godot_instance_method method = { NULL, NULL, NULL };
	
	method.method = &ns_xml_doc_use_case_sensitive_search;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "use_case_sensitive_search", attributes, method);
	
	method.method = &ns_xml_doc_case_sensitive_enabled;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "case_sensitive_enabled", attributes, method);
	
	method.method = &ns_xml_doc_select_root;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "select_root", attributes, method);
	
	method.method = &ns_xml_doc_select_child;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "select_child", attributes, method);
	
	method.method = &ns_xml_doc_select_sibling;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "select_sibling", attributes, method);
	
	method.method = &ns_xml_doc_select_parent;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "select_parent", attributes, method);
	
	method.method = &ns_xml_doc_select_xpath;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "select_xpath", attributes, method);
	
	method.method = &ns_xml_doc_select_next_sibling;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "select_next_sibling", attributes, method);
	
	method.method = &ns_xml_doc_find_child;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "find_child", attributes, method);
	
	method.method = &ns_xml_doc_get_tag_name;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_tag_name", attributes, method);
	
	method.method = &ns_xml_doc_get_children_tag_names;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_children_tag_names", attributes, method);
	
	method.method = &ns_xml_doc_set_attribute_value;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "set_attribute_value", attributes, method);
	
	method.method = &ns_xml_doc_append_attribute_value;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "append_attribute_value", attributes, method);
	
	method.method = &ns_xml_doc_get_attribute_value;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_attribute_value", attributes, method);
	
	method.method = &ns_xml_doc_set_attributes;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "set_attributes", attributes, method);
	
	method.method = &ns_xml_doc_get_attributes;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_attributes", attributes, method);
	
	method.method = &ns_xml_doc_unset_attribute;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "unset_attribute", attributes, method);
	
	method.method = &ns_xml_doc_set_text;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "set_text", attributes, method);
	
	method.method = &ns_xml_doc_append_text;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "append_text", attributes, method);
	
	method.method = &ns_xml_doc_get_text;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_text", attributes, method);
	
	method.method = &ns_xml_doc_create_root_node;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "create_root_node", attributes, method);
	
	method.method = &ns_xml_doc_create_child_node;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "create_child_node", attributes, method);
	
	method.method = &ns_xml_doc_delete_child_node_at;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "delete_child_node_at", attributes, method);
	
	method.method = &ns_xml_doc_delete_selected_node;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "delete_selected_node", attributes, method);
	
	method.method = &ns_xml_doc_has_child;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "has_child", attributes, method);
	
	method.method = &ns_xml_doc_has_attribute;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "has_attribute", attributes, method);
	
	method.method = &ns_xml_doc_has_text;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "has_text", attributes, method);
	
	method.method = &ns_xml_doc_open;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "open", attributes, method);
	
	method.method = &ns_xml_doc_save;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "save", attributes, method);
	
	method.method = &ns_xml_doc_parse;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "parse", attributes, method);
	
	method.method = &ns_xml_doc_to_string;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "to_string", attributes, method);
	
	method.method = &ns_xml_doc_set_encoding;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "set_encoding", attributes, method);
	
	method.method = &ns_xml_doc_get_encoding;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_encoding", attributes, method);
	
	method.method = &ns_xml_doc_set_version;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "set_version", attributes, method);
	
	method.method = &ns_xml_doc_get_version;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_version", attributes, method);
	
	method.method = &ns_xml_doc_get_version_major;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_version_major", attributes, method);
	
	method.method = &ns_xml_doc_get_version_minor;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_version_minor", attributes, method);
	
}






