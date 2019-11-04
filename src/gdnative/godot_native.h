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
#ifndef GDN_C_NATIVE_H
#define GDN_C_NATIVE_H
#include <gdnative_api_struct.gen.h>

const godot_gdnative_core_api_struct *api = NULL;

#ifdef ENABLE_NATIVESCRIPT
const godot_gdnative_ext_nativescript_api_struct *nativescript_api = NULL;
void GDN_EXPORT godot_nativescript_init(void *p_handle);
#endif

// sub components don't need to check GDN_C_NATIVE_H
#define GDN_C_SUB_NATIVE_H

#include "godot_macros.h"



void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options) {
	api = p_options->api_struct;
	
#ifdef ENABLE_NATIVESCRIPT
	for (int i = 0; i < api->num_extensions; i++) {
		switch (api->extensions[i]->type) {
			case GDNATIVE_EXT_NATIVESCRIPT:
				nativescript_api = (godot_gdnative_ext_nativescript_api_struct *) api->extensions[i];
			break;
			default:
			break;
		}
	}
#endif
}

void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options) {
	api = NULL;
#ifdef ENABLE_NATIVESCRIPT
	nativescript_api = NULL;
#endif
}



#endif

