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

// $name is module name

#include "../../pcg/dsquare_hmap.h"
#include "../../pcg/octree_turtle.h"
#include "../../pcg/split_tiled_map_drawer.h"

// include before "test_*.h"
#include "../test.h"

#include "test_dsquare_hmap.h"
#include "test_octree_turtle.h"
#include "test_split_tmd.h"



int test_pcg( )
{
	_test_feature( "dsquare_hmap", test_dsquare_hmap );
	_test_feature( "octree_turtle", test_octree_turtle );
	_test_feature( "split_tiled_map_drawer", test_split_tmd );
	
	return 0;
}


