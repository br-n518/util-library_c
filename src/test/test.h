/* test.h
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


