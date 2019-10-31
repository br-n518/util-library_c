
#include "test.h"

#include "pcg/main_test.h"
#include "terrain/main_test.h"
#include "util/main_test.h"

int main()
{
	_test_feature( "test_util", test_util );
	_test_feature( "test_terrain", test_terrain );
	_test_feature( "test_pcg", test_pcg );
	
	return 0;
}

