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
#ifndef GDN_C_MACROS_H
#define GDN_C_MACROS_H

/**

GD_VARIANT_OBJECT(VAR,OBJ_NAME)
- Init godot_variant to godot_object by class name.
- OBJ_NAME is a C string.
- Calls GD_PRINT when OBJ_NAME isn't recognized by Godot, unless NDEBUG is defined (blindly call potential null pointer).

GD_METHOD_PREPARE()
- Allow calls to GD_METHOD_CALL or GD_METHOD_CALL_RET

GD_METHOD_FINISH()
- Called after GD_METHOD_PREPARE and after call method calls are complete.

GD_METHOD_CALL(SELF,NAME,ARGS,ARGC)
- SELF is godot_variant ptr and NAME is method name (C str).
- ARGS can be NULL or:
	godot_variant *args = (godot_variant[]) {a, b, c};
	GD_METHOD_CALL(_,_, &args, 3)

GD_METHOD_CALL_RET(SELF,NAME,ARGS,ARGC,RET)
- RET = GD_METHOD_CALL(SELF,NAME,ARGS,ARGC)

GD_METHOD_SINGLE_CALL(SELF,NAME,ARGS,ARGC)
- Calls PREPARE and FINISH for you.

GD_METHOD_IS_CALL_OK()
- Use after GD_METHOD_CALL etc.

GD_PRINT(C_STR)
- Create godot_string (in braces code-block) to automate godot_print calls.

GD_PRINT_WITH(C_STR,GD_STR)
- Used for many successive calls, to recycle one godot_string.
- Usage:
	godot_string s;
	api->godot_string_new(&s);
	GD_PRINT_WITH("Hello", &s)

**/

#ifndef NDEBUG
#	define GD_VARIANT_OBJECT(VAR,OBJ_NAME) {\
		godot_class_constructor cstr = api->godot_get_class_constructor(OBJ_NAME);\
		if ( ! cstr ) {api->godot_variant_new_nil(VAR);GD_PRINT("ERROR: No class with name:")GD_PRINT(OBJ_NAME)}\
		else api->godot_variant_new_object(VAR,cstr());}
#else
#	define GD_VARIANT_OBJECT(VAR,OBJ_NAME) \
		api->godot_variant_new_object(VAR,api->godot_get_class_constructor(OBJ_NAME)());
#endif

#define GD_RETURN_NIL() {\
	godot_variant ret;api->godot_variant_new_nil(&ret);\
	return ret;}

#define GD_RETURN_INT(N) {\
	godot_variant ret;api->godot_variant_new_int(&ret,N);\
	return ret;}


// Call once per function.
#define GD_METHOD_PREPARE() \
		godot_string gdmtd_m_name;\
		api->godot_string_new(&gdmtd_m_name);\
		godot_variant_call_error gdmtd_m_e;

// GD_METHOD_CALL( godot_variant*, char*, const godot_variant**, int )
// godot_variant arg1; ...
// const godot_variant *args = (godot_variant[]) {arg1, arg2, ...}; -> ARGC
// Can't define static arg list without [], and can't pass array. (HAS to be (const godot_variant**))
#define GD_METHOD_CALL(SELF,NAME,ARGS,ARGC) \
		api->godot_string_parse_utf8(&gdmtd_m_name, NAME);\
		api->godot_variant_call(SELF,&gdmtd_m_name,(const godot_variant**)ARGS,ARGC,&gdmtd_m_e);

#define GD_METHOD_CALL_RET(SELF,NAME,ARGS,ARGC,RET) \
		api->godot_string_parse_utf8(&gdmtd_m_name, NAME);\
		RET=api->godot_variant_call(SELF,&gdmtd_m_name,(const godot_variant**)ARGS,ARGC,&gdmtd_m_e);


// Call once per function
#define GD_METHOD_FINISH() api->godot_string_destroy(&gdmtd_m_name);



// If you call just one variant method in your function.
// Otherwise use PREPARE, multiple CALL lines, and then FINISH
// You still need to build the arg list.
#define GD_METHOD_SINGLE_CALL(SELF,NAME,ARGS,ARGC) \
		GD_METHOD_PREPARE()\
		GD_METHOD_CALL(SELF,NAME,ARGS,ARGC)\
		GD_METHOD_FINISH()

// check if error was OK
#define GD_METHOD_IS_CALL_OK() (gdmtd_m_e.error==GODOT_CALL_ERROR_CALL_OK)
#define GD_METHOD_CALL_ERROR() (gdmtd_m_e.error)

#define GD_PRINT(C_STR) {\
	godot_string s;api->godot_string_new(&s);\
	api->godot_string_parse_utf8(&s,C_STR);api->godot_print(&s);\
	api->godot_string_destroy(&s);}


#define GD_PRINT_WITH(C_STR,GD_STR) {\
	api->godot_string_parse_utf8(GD_STR,C_STR);\
	api->godot_print(GD_STR);}

#endif

