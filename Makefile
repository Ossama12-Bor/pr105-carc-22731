IGRAPH_PATH ?= /net/npers/renault/save/igraph-0.10.10/install

CFLAGS = -std=gnu99 -Wall -Wextra -Wno-trampolines -fPIC -g3\
	-I$(IGRAPH_PATH)/include/igraph
IGRAPH_LIBDIR = $(shell [ -e $(IGRAPH_PATH)/lib ] && \
        echo $(IGRAPH_PATH)/lib || \
        echo $(IGRAPH_PATH)/lib64)
LDFLAGS = -ligraph -lm -ldl -L$(IGRAPH_LIBDIR) -Wl,--rpath=$(IGRAPH_LIBDIR)

BASE_FILES = \
        deck.c

OBJS = build/liste.o build/board.o build/deck.o build/tile.o build/graph.o build/playerStruct.o build/player_functions.o
all: build 

build: server client build/deck.o

build/%.o: src/%.c
	$(CC) $< $(CFLAGS) -c -o $@ 


server: build/server.o $(OBJS)
	gcc $(OBJS) build/server.o $(LDFLAGS) -o install/server

client:	$(OBJS)
	gcc -fPIC -shared -o install/libplayer1.so $(OBJS) src/players/player1.c -I src $(CFLAGS) -L install
	gcc -fPIC -shared -o install/libplayer2.so $(OBJS) src/players/player2.c -I src $(CFLAGS) -L install

alltests: $(OBJS) build/test_list.o build/test_tile.o build/test_board.o build/test_graph.o build/test_player_functions.o build/alltest.o
#	mkdir -p install/tests
#	gcc $(OBJS) build/test_list.o -o install/tests/test_list -I src -I tst $(LDFLAGS)
#	gcc $(OBJS) build/test_tile.o -o install/tests/test_tile -I src -I tst $(LDFLAGS)
#	gcc $(OBJS) build/test_board.o -o install/tests/test_board -I src -I tst $(LDFLAGS)
#	gcc $(OBJS) build/test_graph.o -o install/tests/test_graph -I src -I tst $(LDFLAGS)
#	gcc $(OBJS) build/test_player_functions.o -o install/tests/test_player_functions -I src -I tst $(LDFLAGS)
	gcc -- coverage $^ -o install/alltests -I src -I tst $(LDFLAGS)
build/%.o: tst/%.c 
	$(CC) -c $< $(CFLAGS) -I src -I tst -o $@


test: alltests

install: server client test

show:
	dot -Kfdp -n -Tpng -o game.png test.dot
	eog game.png

clean:
	@rm -f *~ src/*~ *.o build/*.o -r install/tests *.png

.PHONY: client install test clean
