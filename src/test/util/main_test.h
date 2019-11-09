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
// include pertinent
#include "../../util/all.h"

// include before "test_*.h"
#include "../test.h"

#include "test_btree.h"
#include "test_grammar.h"
#include "test_graph.h"
#include "test_hash.h"
#include "test_ini_doc.h"
#include "test_node.h"
#include "test_strbuff.h"
#include "test_vector_str.h"
#include "test_xml_doc.h"



int test_util( )
{
	int ret = 1;
	
	if ( ! _test_feature( "btree",		test_btree		) ) ret = 0;
	if ( ! _test_feature( "grammar",	test_grammar	) ) ret = 0;
	if ( ! _test_feature( "graph",		test_graph		) ) ret = 0;
	if ( ! _test_feature( "hash",		test_hash		) ) ret = 0;
	if ( ! _test_feature( "ini_doc",	test_ini_doc	) ) ret = 0;
	if ( ! _test_feature( "node",		test_node		) ) ret = 0;
	if ( ! _test_feature( "strbuff",	test_strbuff	) ) ret = 0;
	if ( ! _test_feature( "vec_str",	test_vector_str) ) ret = 0;
	if ( ! _test_feature( "xml_doc",	test_xml_doc	) ) ret = 0;
	
	return ret;
}


