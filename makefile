CC=g++
CFLAGS=-lncurses

all: snake

snake: *.cpp
	$(CC) $^ $(CFLAGS) -o $@

run: snake
	./$^

clean:
	rm -rf snake