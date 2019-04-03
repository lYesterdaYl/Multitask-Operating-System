
main: main.o parse.o
	gcc -o output main.o parse.o

main.o: main.c
	gcc -c main.c

parse.o: parse.c parse.h
	gcc -c parse.c

clean:
	rm -f *.o main core.*
