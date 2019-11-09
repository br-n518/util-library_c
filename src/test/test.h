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
#ifndef ___TEST_FUNCTIONS_H___FRAGMENTS_
#define ___TEST_FUNCTIONS_H___FRAGMENTS_

#include <stdio.h>




// non-terminating assert for testing
// to be read assertive( "function", function_success_condition )
// A short desc string fo the id, and a condition representing affirmative.
int assertive( const char *id, const int condition )
{
#	ifndef NDEBUG
		printf("[ %s ] %s\n", id, condition ? "SUCCESS!" : "FAILED (T_T)" );
		fflush( stdout );
#	endif
	return condition;
	// returns condition so assertive can be placed in if statements
}





/**
 * @brief Run a test procedure, returning char as boolean, then print success or failure.
 * @param id Printed ID string for clarity.
 * @param func Test function to call. Must take no args and return char.
 * @returns Returns nothing, but the pointer @p func must return char.
 */
int _test_feature ( const char *id, int (*func)(void) )
{
	int res = func();

	printf("|%s| %s\n", id, res ? "SUCCESS!" : "FAILED (T_T)" );
	fflush( stdout );
	
	return res;
}





#endif


