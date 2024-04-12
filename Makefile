IGRAPH_PATH ?= /net/npers/renault/save/igraph-0.10.10/install
#IGRAPH_PATH_IHATTI = /usr/local/lib/
CFLAGS = -std=gnu99 -Wall -Wextra -Wno-trampolines -fPIC -g3 \
	-I$(IGRAPH_PATH)/include/igraph
LDFLAGS = -ligraph -lm -ldl -L$(IGRAPH_PATH)/lib -Wl,--rpath=${IGRAPH_PATH}/lib

BASE_FILES = \
        deck.c

OBJS=liste.o board.o deck.o tile.o
all: build

build: server client deck.o

%.o: src/%.c
	$(CC) $< $(CFLAGS) -c

server:

client:
	gcc -fPIC -shared -o install/libplayer1.so src/players/player1.c -L install
#	gcc -fPIC -shared -o libplayer2.so src/players/player2.c -L install

alltests: $(OBJS) test_list.o test_tile.o test_board.o
	gcc $(OBJS) test_list.o -o test -I src -I tst 
	gcc $(OBJS) test_tile.o -o testtile -I src -I tst
	gcc $(OBJS) test_board.o -o testboard -I src -I tst 

%.o: src/%.c
	$(CC) -c $< $(CFLAGS) 
%.o: tst/%.c 
	$(CC) -c $< $(CFLAGS) -I src
test: alltests

install: server client test

clean:
	@rm -f *~ src/*~ *.o

.PHONY: client install test clean
