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
int test_node()
{
	int ret = 1;
	
	int data1 = 40;
	int data2 = 50;
	int data3 = 60;
	int data4 = 80;
	
	node_t *head = node_create( &data1 );
	
	node_insert_after( head, node_create( &data2 ) );
	node_insert_after( head->next, node_create( &data3 ));
	
	node_push_back( &head, &data4 );
	
	node_t *copy = node_copy_chain( head );
	
	if ( ! assertive("node_copy_chain", copy != head && copy->data == head->data ) )
	{
		ret = 0;
	}
	node_free_chain(copy);
	copy = 0;
	
	if ( ! assertive("node_count", node_count(head) == 4 ))
	{
		ret = 0;
	}
	
	if ( ! assertive("node_insert_after", head->next->next->next && !( head->next->next->next->next ) ) )
	{
		ret = 0;
	}
	
	if ( ! assertive("node_has", node_has(head, &data1) &&
			node_has( head, &data2 ) &&
			node_has( head, &data3 ) &&
			node_has( head, &data4 ) ))
	{
		ret = 0;
	}
	
	int *p = (int*) node_pop( &head, head->next);
	if ( ! assertive("node_pop", *p == data2 && !( head->next->next->next ) ) )
	{
		ret = 0;
	}
	
	node_remove( &head, &data3 );
	if ( ! assertive("node_remove", !( head->next->next ) && !(node_has(head, &data3)) ))
	{
		ret = 0;
	}
	p = (int*) node_pop( &head, head );
		
	if ( ! assertive("node_pop head", !(head->next) && p == &data1 ) )
	{
		ret = 0;
	}
	
	p = (int*) node_pop(&head, head);
	
	if ( ! assertive("node_pop head final", !head && p == &data4 ) )
	{
		ret = 0;
	}
	
	return ret;
}

