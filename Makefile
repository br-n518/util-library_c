# TOOLS
CC=gcc

# INPUT FILES
UTIL_SRC=src/util/*.c
TERRAIN_SRC=src/terrain/*.c
PCG_SRC=src/pcg/*.c
SRC=$(UTIL_SRC) $(TERRAIN_SRC) $(PCG_SRC) src/rand/rnd.c

# OUT FILE
SHARED_EXT=.so
EXEC_EXT=.out

OUTPUT_NAME=libpcg
OUTPUT_SHARED=$(OUTPUT_NAME)$(SHARED_EXT)
OUTPUT_EXEC=$(OUTPUT_NAME)$(EXEC_EXT)

# COMPILE
CFLAGS=-std=c99 -Wall -Werror

# LINK
LDFLAGS=

# GODOT
GDSRC=$(SRC) src/godot.c
GDFLAGS=$(CFLAGS) -I"godot_headers" -D"GODOT"

# GODOT PROJECT
DEPLOY=godot_project/lib/$(OUTPUT_SHARED)

.PHONY: test test_quiet
.PHONY: all clean shared
.PHONY: godot deploy
.PHONY: ns_ini_doc



shared: clean build_shared
	# LINK
	$(CC) -shared -o bin/$(OUTPUT_SHARED) *.o $(LDFLAGS)



godot: clean build_godot
	# LINK
	$(CC) -shared -o bin/$(OUTPUT_SHARED) *.o $(LDFLAGS)



all: clean shared



.PHONY: build_shared
build_shared: $(SRC)
	# COMPILE
	$(CC) -c -fPIC $(CFLAGS) $(SRC)

.PHONY: build_godot
build_godot: $(SRC)
	# COMPILE
	$(CC) -c -fPIC $(GDFLAGS) $(GDSRC)



clean:
	# CLEAN
	rm -f *.o



deploy: bin/$(OUTPUT_SHARED)
	# DEPLOY
	cp bin/$(OUTPUT_SHARED) $(DEPLOY)



TEST_SRC=src/test/test_main.c $(SRC)
TEST_LDFLAGS=$(LDFLAGS)

test: $(TEST_SRC)
	# BUILD TEST
	$(CC) $(CFLAGS) -ggdb -o bin/test$(EXEC_EXT) $(TEST_SRC) $(TEST_LDFLAGS)

test_quiet: $(TEST_SRC)
	# BUILD TEST
	$(CC) $(CFLAGS) -D"NDEBUG" -o bin/test$(EXEC_EXT) $(TEST_SRC) $(TEST_LDFLAGS)



# NativeScript
NS_INI_DOC_SRC=src/nativescript_ini_doc.c src/util/ini_doc.c src/util/strbuff.c src/util/hash.c

ns_ini_doc: src/nativescript_ini_doc.c
	# BUILD NativeScript ini_doc
	$(CC) -fPIC -shared $(GDFLAGS) -D"ENABLE_NATIVESCRIPT" $(NS_INI_DOC_SRC) -o bin/ini_doc$(SHARED_EXT)

#~ NS_XML_DOC_SRC=src/nativescript_xml_doc.c src/util/xml_doc.c src/util/strbuff.c src/util/hash.c src/util/node.c
#~ ns_xml_doc: src/nativescript_xml_doc.c
#~ 	# BUILD NativeScript xml_doc
#~ 	$(CC) -fPIC -shared $(GDFLAGS) -D"ENABLE_NATIVESCRIPT" $(NS_XML_DOC_SRC) -o bin/xml_doc$(SHARED_EXT)







