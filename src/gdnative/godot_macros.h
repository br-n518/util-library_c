/* godot_macros.h
 *
 * Copyright (c) 2019 br-n518
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef GDN_C_MACROS_H
#define GDN_C_MACROS_H

/** API

GD_VARIANT_OBJECT(VAR,OBJ_NAME)
- Init godot_variant to godot_object by class name.
- OBJ_NAME is a C string.
- Calls GD_PRINT when OBJ_NAME isn't recognized by Godot, unless NDEBUG is defined (blindly call potential null pointer).

GD_METHOD_PREPARE()
- Allow calls to GD_METHOD_CALL or GD_METHOD_CALL_RET

GD_METHOD_FINISH()
- Called after GD_METHOD_PREPARE and after all method calls are complete.

GD_METHOD_CALL(SELF,NAME,ARGS,ARGC)
- SELF is godot_variant ptr and NAME is method name (C str).
- ARGS can be NULL or:
	godot_variant *args = (godot_variant[]) {a, b, c};
	GD_METHOD_CALL(_,_, &args, 3)

GD_METHOD_CALL_RET(SELF,NAME,ARGS,ARGC,RET)
- RET = GD_METHOD_CALL(SELF,NAME,ARGS,ARGC)

GD_METHOD_SINGLE_CALL(SELF,NAME,ARGS,ARGC)
- Calls PREPARE, METHOD_CALL and FINISH.

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
	GD_PRINT_WITH("World", &s)
	api->godot_string_destroy(&s);

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
	godot_variant _ret;api->godot_variant_new_nil(&_ret);\
	return _ret;}

#define GD_RETURN_INT(N) {\
	godot_variant _ret;api->godot_variant_new_int(&_ret,N);\
	return _ret;}


// Call once per function body.
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


// Call once per function body.
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
	godot_string gd_str_s;api->godot_string_new(&gd_str_s);\
	api->godot_string_parse_utf8(&gd_str_s,C_STR);api->godot_print(&gd_str_s);\
	api->godot_string_destroy(&gd_str_s);}


#define GD_PRINT_WITH(C_STR,GD_STR) {\
	api->godot_string_parse_utf8(GD_STR,C_STR);\
	api->godot_print(GD_STR);}


#define GD_PV3A_APPEND(_pv3a, _v3, _x,_y,_z) \
	api->godot_vector3_new(_v3,_x,_y,_z);\
	api->godot_pool_vector3_array_append(_pv3a,_v3);

#define GD_PV2A_APPEND(_pv2a, _v2, _x,_y) \
	api->godot_vector2_new(_v2,_x,_y);\
	api->godot_pool_vector2_array_append(_pv2a,_v2);






#endif

