CC=g++
CFLAGS=-lncurses

all: snake

release: *.cpp
	$(CC) $^ $(CFLAGS) -O2 -o $@

snake_debug: *.cpp
	$(CC) $^ $(CFLAGS) -o $@

run: snake_debug
	./$^

clean:
	rm -rf snake