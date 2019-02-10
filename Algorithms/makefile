all:test P1 P12 P21 P22

test:
	gcc -Wall -std=c99 main.c -o test

P1:
	gcc -Wall -std=c99 P1.c -o p1

P12:
	gcc -Wall -std=c99 P12.c -o p12

P21:
	gcc -Wall -std=c99 P21.c -o p21

P22:
		gcc -Wall -std=c99 P22.c -o p22 -lm

valgrind:
	valgrind --track-origins=yes ./p22


clean:
	rm test p1 p12 p21
