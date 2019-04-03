all: parse.tab.c lex.yy.c
	gcc -w parse.tab.c lex.yy.c parse.c cd.c -o nsh

parse.tab.c: parse.y
	bison -d parse.y;

lex.yy.c: parse.l
	flex parse.l;

run: all
	./nsh

clean:
	rm -f nsh parse.tab.h parse.tab.c lex.yy.c
