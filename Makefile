IGRAPH_PATH ?= /net/npers/renault/save/igraph-0.10.10/install

CFLAGS = -std=gnu99 -Wall -Wextra -Wno-trampolines -fPIC -g3 \
	-I$(IGRAPH_PATH)/include/igraph
IGRAPH_LIBDIR = $(shell [ -e $(IGRAPH_PATH)/lib ] && \
        echo $(IGRAPH_PATH)/lib || \
        echo $(IGRAPH_PATH)/lib64)
LDFLAGS = -ligraph -lm -ldl -L$(IGRAPH_LIBDIR) -Wl,--rpath=$(IGRAPH_LIBDIR)

BASE_FILES = \
        deck.c

OBJS = build/liste.o build/board.o build/deck.o build/tile.o build/graph.o build/playerStruct.o

all: build

build: server client build/deck.o

build/%.o: src/%.c
	$(CC) $< $(CFLAGS) -c -o $@

server: build/server.o $(OBJS)
	gcc $(OBJS) build/server.o $(LDFLAGS) -o install/server

client:	$(OBJS)
	gcc -fPIC -shared -o install/libplayer1.so $(OBJS) src/players/player1.c -I src -L install
#	gcc -fPIC -shared -o libplayer2.so src/players/player2.c -L install

alltests: $(OBJS) build/test_list.o build/test_tile.o build/test_board.o build/test_graph.o
	mkdir -p install/tests
	gcc $(OBJS) build/test_list.o -o install/tests/test_list -I src -I tst $(LDFLAGS)
	gcc $(OBJS) build/test_tile.o -o install/tests/test_tile -I src -I tst $(LDFLAGS)
	gcc $(OBJS) build/test_board.o -o install/tests/test_board -I src -I tst $(LDFLAGS)
	gcc $(OBJS) build/test_graph.o -o install/tests/test_graph -I src -I tst $(LDFLAGS)

build/%.o: tst/%.c 
	$(CC) -c $< $(CFLAGS) -I src -o $@

test: alltests

install: server client test

clean:
	@rm -f *~ src/*~ *.o build/*.o -r install/tests

.PHONY: client install test clean
