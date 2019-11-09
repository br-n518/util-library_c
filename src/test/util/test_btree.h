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
int test_btree() {
	int ret = 0;
	
	const int key1 = 2;
	const int key2 = 3;
	const int key3 = 1;
	const int key4 = 10;
	
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int data4 = 40;
	
	btree head;
	bt_init( &head, key1, &data1 );
	
	//bt_put( head, key1, &data1 );
	bt_put( &head, key2, &data2 );
	bt_put( &head, key3, &data3 );
	bt_put( &head, key4, &data4 );
	
	if ( bt_get_node(&head, key3)->data == &data3 &&
				bt_get_node(&head, key4)->data == &data4 &&
				bt_get_data(&head, key1) == &data1) {
		
		ret = 1;
	}
	bt_clear( &head );
	
	return ret;
}


