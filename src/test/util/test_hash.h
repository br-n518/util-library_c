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
int test_hash() {
	int ret = 0;
	
	hash_table table;
	ht_init( &table );
	
	int data1 = 20;
	int data2 = 30;
	int data3 = 40;
	
	ht_set( &table, "asdf", 4, &data1 );
	ht_set( &table, "qwer", 4, &data2 );
	ht_set( &table, "gggg", 4, &data3 );
	ht_set( &table, "qwer", 4, &data1 );
	
	if ( ht_get( &table, "qwer", 4 ) == &data1 ) {
	
		ht_remove( &table, &data3 );
		if ( !( ht_has( &table, "gggg", 4 ) ) ) {
		
			ht_unset( &table, "asdf", 4 );
			if ( !( ht_has( &table, "asdf", 4 ) ) ) {
			
				ret = 1;
			}
		}
	}
	
	// allocates memory when keys collide, so clean up with ht_clear
	ht_clear( &table );
	
	return ret;
}


