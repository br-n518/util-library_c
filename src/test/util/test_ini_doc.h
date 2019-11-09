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
int test_ini_doc()
{
	struct ini_doc *ddoc = _MALLOC( sizeof(*ddoc) );
	ini_doc_init( ddoc );
	
	char ret = ini_doc_load( ddoc, "test/test.ini" );
	
	if ( ret )
	{
		ini_doc_set_global( ddoc, "monkey", "Mankey");
		
		ini_doc_set( ddoc, "asdf", "elephant", "donphan" );
		
		ini_doc_save( ddoc, "test/result__test.ini" );
		
		//ret = 0;
		if ( ! assertive("ini_doc_get", strcmp( ini_doc_get(ddoc,"asdf","elephant"), "donphan" ) == 0 ) )
		{
			ret = 0;
		}
		if ( ! assertive("ini_doc_get_global", strcmp( ini_doc_get_global(ddoc,"monkey"), "Mankey" ) == 0 ) )
		{
			ret = 0;
		}
		
	}
	
	ini_doc_destroy( ddoc );
	_FREE( ddoc );
	
	return ret;
}


