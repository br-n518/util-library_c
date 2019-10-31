#ifndef _MALLOC
#	ifdef GODOT
#		include "gdnative/godot_sub_native.h"
#		define _MALLOC api->godot_alloc
#		define _FREE api->godot_free
#	else
#		include <stdlib.h>
#		define _MALLOC malloc
#		define _FREE free
#	endif
#endif

