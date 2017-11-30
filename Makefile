all: example

example: object.c derived.c doublederived.c main.c idrawable.c
	gcc -Wall -pedantic -g -std=c99 -o $@ $^
	
clean:
	rm -f example
