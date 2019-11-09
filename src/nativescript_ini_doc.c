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
#include "gdnative/godot_native.h"

#include "util/ini_doc.h"

GDCALLINGCONV void* ns_ini_doc_constructor(godot_object *p_instance, void *p_method_data)
{
	
	struct ini_doc *data = api->godot_alloc( sizeof(*data) );
	ini_doc_init( data );
	return data;
}

GDCALLINGCONV void ns_ini_doc_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data)
{
	ini_doc_destroy( p_user_data );
	api->godot_free( p_user_data );
}





godot_variant ns_ini_doc_get(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	if ( p_num_args >= 2 )
	{
		// get args
		godot_string sect_str = api->godot_variant_as_string(p_args[0]);
		godot_string key_str = api->godot_variant_as_string(p_args[1]);
		
		// convert section arg
		godot_char_string cs_s = api->godot_string_ascii(&sect_str);
		api->godot_string_destroy(&sect_str);
		
		// convert key arg
		godot_char_string cs_k = api->godot_string_ascii(&key_str);
		api->godot_string_destroy(&key_str);
		
		// call ini_doc_get
		// NOTE: val isn't allocated, no need for _FREE
		char *val = ini_doc_get( doc,
				api->godot_char_string_get_data(&cs_s),
				api->godot_char_string_get_data(&cs_k) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_s );
		api->godot_char_string_destroy( &cs_k );
		
		// check value exists
		if ( val )
		{
			// reuse key_str for godot_string
			api->godot_string_new(&key_str);
			api->godot_string_parse_utf8(&key_str, val);
			
			// variant return type
			godot_variant var;
			api->godot_variant_new_string(&var, &key_str);
			// cleanup
			api->godot_string_destroy( &key_str );
			
			return var;
		}
	}
	GD_RETURN_NIL()
}

godot_variant ns_ini_doc_get_global(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	if ( p_num_args >= 1 )
	{
		// get arg
		godot_string key_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_k = api->godot_string_ascii(&key_str);
		api->godot_string_destroy(&key_str);
		
		// call ini_doc_get_global
		// NOTE: val isn't allocated, no need for _FREE
		char *val = ini_doc_get_global( doc, api->godot_char_string_get_data(&cs_k) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_k );
		
		// check value exists
		if ( val )
		{
			// reuse key_str for godot_string
			api->godot_string_new(&key_str);
			api->godot_string_parse_utf8(&key_str, val);
			
			// variant return type
			godot_variant var;
			api->godot_variant_new_string(&var, &key_str);
			// cleanup
			api->godot_string_destroy( &key_str );
			
			return var;
		}
	}
	GD_RETURN_NIL()
}


godot_variant ns_ini_doc_set(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	if ( p_num_args >= 3 )
	{
		// get args
		godot_string sect_str = api->godot_variant_as_string(p_args[0]);
		godot_string key_str = api->godot_variant_as_string(p_args[1]);
		godot_string value_str = api->godot_variant_as_string(p_args[2]);
		
		// convert section arg
		godot_char_string cs_s = api->godot_string_ascii(&sect_str);
		api->godot_string_destroy(&sect_str);
		
		// convert key arg
		godot_char_string cs_k = api->godot_string_ascii(&key_str);
		api->godot_string_destroy(&key_str);
		
		// convert value arg
		godot_char_string cs_v = api->godot_string_ascii(&value_str);
		api->godot_string_destroy(&value_str);
		
		// call ini_doc_set
		ini_doc_set( doc,
				api->godot_char_string_get_data(&cs_s),
				api->godot_char_string_get_data(&cs_k),
				api->godot_char_string_get_data(&cs_v) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_s );
		api->godot_char_string_destroy( &cs_k );
		api->godot_char_string_destroy( &cs_v );
		
	}
	GD_RETURN_NIL()
}

godot_variant ns_ini_doc_set_global(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	if ( p_num_args >= 2 )
	{
		// get args
		godot_string key_str = api->godot_variant_as_string(p_args[0]);
		godot_string value_str = api->godot_variant_as_string(p_args[1]);
		
		// convert key arg
		godot_char_string cs_k = api->godot_string_ascii(&key_str);
		api->godot_string_destroy(&key_str);
		
		// convert value arg
		godot_char_string cs_v = api->godot_string_ascii(&value_str);
		api->godot_string_destroy(&value_str);
		
		// call ini_doc_set_global
		ini_doc_set_global( doc,
				api->godot_char_string_get_data(&cs_k),
				api->godot_char_string_get_data(&cs_v) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_k );
		api->godot_char_string_destroy( &cs_v );
		
	}
	GD_RETURN_NIL()
}


godot_variant ns_ini_doc_open(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	godot_bool ret = 0;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		
		// call ini_doc_load
		ret = ini_doc_load( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
		
		
	}
	godot_variant ret_var;
	api->godot_variant_new_bool(&ret_var, ret);
	
	return ret_var;
}


godot_variant ns_ini_doc_save(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string fname_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_fname = api->godot_string_ascii(&fname_str);
		api->godot_string_destroy(&fname_str);
		
		// call ini_doc_save
		ini_doc_save( doc,
				api->godot_char_string_get_data(&cs_fname) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_fname );
	}
	GD_RETURN_NIL()
}


godot_variant ns_ini_doc_parse(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	if ( p_num_args >= 1 )
	{
		// get args
		godot_string data_str = api->godot_variant_as_string(p_args[0]);
		
		// convert key arg
		godot_char_string cs_data = api->godot_string_ascii(&data_str);
		api->godot_string_destroy(&data_str);
		
		// call ini_doc_parse
		ini_doc_parse( doc,
				api->godot_char_string_get_data(&cs_data) );
		
		// cleanup
		api->godot_char_string_destroy( &cs_data );
	}
	GD_RETURN_NIL()
}


godot_variant ns_ini_doc_to_string(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	// get object
	struct ini_doc *doc = (struct ini_doc*) p_user_data;
	
	godot_string gd_str;
	api->godot_string_new( &gd_str );
	
	char *cstr = ini_doc_to_string(doc);
	
	godot_variant ret;
	if ( cstr )
	{
		// parse string
		api->godot_string_parse_utf8(&gd_str, cstr);
		_FREE(cstr);
		
		api->godot_variant_new_string( &ret, &gd_str );
	}
	else
	{
		api->godot_variant_new_nil(&ret);
	}
	api->godot_string_destroy( &gd_str );
	
	return ret;
}


void GDN_EXPORT godot_nativescript_init(void *p_handle)
{
	godot_instance_create_func create = { NULL, NULL, NULL };
	create.create_func = &ns_ini_doc_constructor;

	godot_instance_destroy_func destroy = { NULL, NULL, NULL };
	destroy.destroy_func = &ns_ini_doc_destructor;

	nativescript_api->godot_nativescript_register_class(p_handle, "ini_doc", "Node", create, destroy);


	godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };
	godot_instance_method method = { NULL, NULL, NULL };
	
	method.method = &ns_ini_doc_get;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "get", attributes, method);
	
	method.method = &ns_ini_doc_get_global;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "get_global", attributes, method);
	
	method.method = &ns_ini_doc_set;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "set", attributes, method);
	
	method.method = &ns_ini_doc_set_global;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "set_global", attributes, method);
	
	method.method = &ns_ini_doc_save;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "save", attributes, method);
	
	method.method = &ns_ini_doc_open;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "open", attributes, method);
	
	method.method = &ns_ini_doc_parse;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "parse", attributes, method);
	
	method.method = &ns_ini_doc_to_string;
	nativescript_api->godot_nativescript_register_method(p_handle, "ini_doc", "to_string", attributes, method);
}
