cc = gcc
#cc = clang

cflags = -O2 -s -I.
#cflags = -I.

all: pt


pt: pt.l pt.y pt.h main.c utils.c
	bison -b objs/$@ -d $@.y
	flex -o objs/$@.lex.c $@.l
	$(cc) $(cflags) -o bin/$@  objs/$@.tab.c objs/$@.lex.c main.c utils.c



clean:
	-rm objs/* bin/*


