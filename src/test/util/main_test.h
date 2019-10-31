/* 
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


