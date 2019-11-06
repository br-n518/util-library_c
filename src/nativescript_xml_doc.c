
#include "gdnative/godot_native.h"

#include "util/xml_doc.h"


typedef struct ns_xml_doc
{
	struct xml_doc *doc;
	struct xml_node *selected_node;
} ns_xml_doc;


GDCALLINGCONV void* xml_doc_constructor(godot_object *p_instance, void *p_method_data)
{
	ns_xml_doc *data = api->godot_alloc( sizeof( *data ) );
	
	data->doc = xml_doc_create();
	data->selected_node = 0;
	
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
// disabled by default, always match case insensitive

use_case_sensitive_search( b:bool=1 )
case_sensitive_enabled( ) -> bool

// NODE SELECTION

select_root( )
select_child( String ) -> bool
select_sibling( String) -> bool (select_parent then select_child, but noting index via pointer matching)
select_parent( ) -> bool
select_xpath( String ) -> bool (can be relative or absolute, can only select nodes, not attributes or any text values.)

select_next_child( )
select_next_sibling( )

find_child( String )  (searches from current selected node until node with matching name is found)

get_tag_name( ) -> String
get_children_tag_names() -> PoolStringArray

// ATTRIBUTES

set_attribute( String, String )
append_attribute( String, String )
unset_attribute( String )

get_attribute_value( String ) -> String
get_attributes( ) -> Dictionary

// TEXT

set_text( String )
get_text( ) -> String
append_text( String )

// NODE CREATION AND DELETION

create_root_node( String, encoding:String="UTF-8", version:String="1.0" )  (Deletes any XML document contents before creating)
create_child_node( String, idx:int=-1 )
delete_child_node_at( int, connect:bool=0 )  (deletes all child nodes of child by default)
delete_selected_node( connect:bool=0 )  (selects parent, or none if root deleted; deletes all child nodes by default)

// HAS

has_child( String ) -> bool
has_attribute( String ) -> bool
has_text( String, case_sensitive:bool=1 ) -> bool  (case sensitivity here is separate from global tag matching setting)

// FILE-BASED OPERATIONS

open( String )
save( String, xml_header:bool=1 )
parse( String )
to_string( xml_header:bool=0 ) -> String

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






godot_variant ns_xml_doc_open(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct xml_doc *doc = (struct xml_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		
		// call xml_doc_load
		ret = xml_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}


godot_variant ns_xml_doc_save(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct xml_doc *doc = (struct xml_doc*) p_user_data;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		// call xml_doc_load
		xml_doc_save( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
	}
	GD_RETURN_NIL()
}


godot_variant ns_xml_doc_parse(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct xml_doc *doc = (struct xml_doc*) p_user_data;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string data_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_data = api->godot_string_ascii(&data_str);
		// delete string
		api->godot_string_destroy(&data_str);
		
		xml_doc_parse( doc,
				api->godot_char_string_get_data(&cs_data) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_data );
	}
	GD_RETURN_NIL()
}


void GDN_EXPORT godot_nativescript_init(void *p_handle)
{
	godot_instance_create_func create = { NULL, NULL, NULL };
	create.create_func = &ns_xml_doc_constructor;

	godot_instance_destroy_func destroy = { NULL, NULL, NULL };
	destroy.destroy_func = &ns_xml_doc_destructor;

	nativescript_api->godot_nativescript_register_class(p_handle, "xml_doc", "Node", create, destroy);


	godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };
	godot_instance_method method = { NULL, NULL, NULL };
	
	method.method = &ns_xml_doc_get;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get", attributes, method);
	
	method.method = &ns_xml_doc_get_global;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "get_global", attributes, method);
	
	method.method = &ns_xml_doc_set;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "set", attributes, method);
	
	method.method = &ns_xml_doc_set_global;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "set_global", attributes, method);
	
	method.method = &ns_xml_doc_save;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "save", attributes, method);
	
	method.method = &ns_xml_doc_open;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "open", attributes, method);
	
	method.method = &ns_xml_doc_parse;
	nativescript_api->godot_nativescript_register_method(p_handle, "xml_doc", "parse", attributes, method);
	
}






