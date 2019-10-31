# TOOLS
CC=gcc
CXX=g++

# INPUT FILES
UTIL_SRC=src/util/*.c
TERRAIN_SRC=src/terrain/*.c
SRC=$(UTIL_SRC) src/terrain/*.c src/pcg/*.c

# OUT FILE
OUTPUT_FILE=libpcg
SHARED_EXT=.so
OUTPUT_SHARED=$(OUTPUT_FILE)$(SHARED_EXT)
EXEC_EXT=.out
OUTPUT_EXEC=$(OUTPUT_FILE)$(EXEC_EXT)

# COMPILE
CFLAGS=-std=c99 -Wall -Werror
CXXFLAGS=-std=c++11 -Wall -Werror -O3

# LINK
LDFLAGS=-lstdc++

# GODOT
GDSRC=$(UTIL_SRC) src/terrain/*.c src/pcg/*.c src/godot.c
GDFLAGS=$(CFLAGS) -I"godot_headers" -D"GODOT"
DEPLOY=godot_project/lib/$(OUTPUT_SHARED)

.PHONY: all clean rand shared build_shared godot build_godot test_util deploy



shared: clean build_shared
	# LINK
	$(CC) -shared -o bin/$(OUTPUT_SHARED) *.o $(LDFLAGS)

godot: clean build_godot
	# LINK
	$(CC) -shared -o bin/$(OUTPUT_SHARED) *.o $(LDFLAGS)


all: clean shared



build_shared: $(SRC) rand
	# COMPILE
	$(CC) -c -fPIC $(CFLAGS) $(SRC)


build_godot: $(SRC) rand
	# COMPILE
	$(CC) -c -fPIC $(GDFLAGS) $(GDSRC)

rand: src/rand/rand.cpp
	$(CXX) -c -fPIC $(CXXFLAGS) src/rand/rand.cpp


clean:
	# REMOVE OBJECTS AND TESTS
	rm -f *.o




deploy: bin/$(OUTPUT_SHARED)
	cp bin/$(OUTPUT_SHARED) $(DEPLOY)


TEST_UTIL_SRC=src/test/util/main_test.c $(UTIL_SRC)
TEST_UTIL_LDFLAGS=
test_util: bin/test_util$(EXEC_EXT)
bin/test_util$(EXEC_EXT): $(TEST_UTIL_SRC)
	# BUILD TEST UTIL
	$(CC) $(CFLAGS) -o bin/test_util$(EXEC_EXT) $(TEST_UTIL_SRC) $(TEST_UTIL_LDFLAGS)




