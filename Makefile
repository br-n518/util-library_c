# TOOLS
CC=gcc
CXX=g++

# INPUT FILES
UTIL_SRC=src/util/*.c
TERRAIN_SRC=src/terrain/*.c
PCG_SRC=src/pcg/*.c
SRC=$(UTIL_SRC) $(TERRAIN_SRC) $(PCG_SRC)

# OUT FILE
SHARED_EXT=.so
EXEC_EXT=.out

OUTPUT_NAME=libpcg
OUTPUT_SHARED=$(OUTPUT_NAME)$(SHARED_EXT)
OUTPUT_EXEC=$(OUTPUT_NAME)$(EXEC_EXT)

# COMPILE
CFLAGS=-std=c99 -Wall -Werror
CXXFLAGS=-std=c++11 -Wall -Werror -O3

# LINK
LDFLAGS=-lstdc++

# GODOT
GDSRC=$(SRC) src/godot.c
GDFLAGS=$(CFLAGS) -I"godot_headers" -D"GODOT"

# GODOT PROJECT
DEPLOY=godot_project/lib/$(OUTPUT_SHARED)



.PHONY: shared
shared: clean build_shared rand.o
	# LINK
	$(CC) -shared -o bin/$(OUTPUT_SHARED) *.o $(LDFLAGS)



.PHONY: godot
godot: clean build_godot rand.o
	# LINK
	$(CC) -shared -o bin/$(OUTPUT_SHARED) *.o $(LDFLAGS)



.PHONY: all
all: clean shared



.PHONY: build_shared
build_shared: $(SRC)
	# COMPILE
	$(CC) -c -fPIC $(CFLAGS) $(SRC)

.PHONY: build_godot
build_godot: $(SRC)
	# COMPILE
	$(CC) -c -fPIC $(GDFLAGS) $(GDSRC)



rand.o: src/rand/rand.cpp
	# COMPILE C++ <random> wrapper
	$(CXX) -c -fPIC $(CXXFLAGS) src/rand/rand.cpp


.PHONY: clean
clean:
	# CLEAN
	rm -f *.o



.PHONY: deploy
deploy: bin/$(OUTPUT_SHARED)
	# DEPLOY
	cp bin/$(OUTPUT_SHARED) $(DEPLOY)



TEST_SRC=rand.o src/test/test_main.c $(SRC)
TEST_LDFLAGS=$(LDFLAGS)

.PHONY: test
test: $(TEST_SRC)
	# BUILD TEST
	$(CC) $(CFLAGS) -ggdb -o bin/test$(EXEC_EXT) $(TEST_SRC) $(TEST_LDFLAGS)

.PHONY: test_quiet
test_quiet: $(TEST_SRC)
	$(CC) $(CFLAGS) -D"NDEBUG" -o bin/test$(EXEC_EXT) $(TEST_SRC) $(TEST_LDFLAGS)


