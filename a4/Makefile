all:
	gcc -std=c99 -Wall p2.c -o test

clean:
	rm -rf test

valgrind:
	valgrind --leak-check=full --track-origins=yes  ./test
