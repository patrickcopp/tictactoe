all: tictactoe.o a1p1 a1p2 a1p3 a1p4 a1p5

tictactoe: tictactoe.o tictactoe.h
	gcc -Wall -ansi -pedantic -c tictactoe.c -o tictactoe.o

a1p1: a1p1.c tictactoe.c tictactoe.h 
	gcc -Wall -ansi -pedantic a1p1.c tictactoe.c -o a1p1

a1p2: a1p2.c tictactoe.c tictactoe.h 
	gcc -Wall -ansi -pedantic a1p2.c tictactoe.c -o a1p2

a1p3: a1p3.c tictactoe.c tictactoe.h 
	gcc -Wall -ansi -pedantic a1p3.c tictactoe.c -o a1p3

a1p4: a1p4.c tictactoe.c tictactoe.h 
	gcc -Wall -ansi -pedantic a1p4.c tictactoe.c -o a1p4

a1p5: a1p5.c tictactoe.c tictactoe.h
	gcc -Wall -ansi -pedantic a1p5.c tictactoe.c -o a1p5
