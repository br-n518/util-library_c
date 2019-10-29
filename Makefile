# TOOLS
CC=gcc
CXX=g++

# INPUT FILES
UTIL_SRC=src/util/*.c
SRC=src/*.c $(UTIL_SRC)

# OUT FILE
OUTPUT_FILE=a
OUTPUT_EXT=.out

# COMPILE
CFLAGS=-std=c99 -Wall -Werror
CXXFLAGS=-std=c++11 -Wall -Werror -O3

# LINK
LDFLAGS=-lstdc++



.PHONY: all clean clean_all test_util doxy



bin/$(OUTPUT_FILE)$(OUTPUT_EXT): clean *.o
	# LINK
	$(CC) -o bin/$(OUTPUT_FILE)$(OUTPUT_EXT) *.o $(LDFLAGS)


all: clean_all test_util bin/$(OUTPUT_FILE)$(OUTPUT_EXT)



*.o: $(SRC) src/util/rand/rand.cpp
	# COMPILE
	$(CC) -c $(CFLAGS) $(SRC)
	$(CXX) -c $(CXXFLAGS) src/util/rand/rand.cpp



clean:
	# REMOVE OBJECTS AND TESTS
	rm -f bin/test_util$(OUTPUT_EXT)
	rm -f *.o

clean_all: clean
	# REMOVE BINARIES
	rm -f bin/$(OUTPUT_FILE)$(OUTPUT_EXT)



TEST_UTIL_SRC=src/test/util/main_test.c $(UTIL_SRC)
TEST_UTIL_LDFLAGS=
test_util: bin/test_util$(OUTPUT_EXT)
bin/test_util$(OUTPUT_EXT): $(TEST_UTIL_SRC)
	# BUILD TEST UTIL
	$(CC) $(CFLAGS) -o bin/test_util$(OUTPUT_EXT) $(TEST_UTIL_SRC) $(TEST_UTIL_LDFLAGS)


doxy: doc/Doxyfile doc/doxygen/
	doxygen doc/Doxyfile



