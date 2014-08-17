cc = gcc
#cc = clang

cflags = -I.

objects = utils.o log.o message.o
analyser = objs/pt.lex.c
parser = objs/pt.tab.c objs/pt.tab.h


all: pt


pt: $(analyser) $(objects)
	$(cc) -O2 -s $(cflags) -o bin/$@  objs/$@.tab.c ${analyser} main.c $(addprefix objs/, $(objects))


$(analyser): $(parser) pt.h
	flex -o objs/pt.lex.c pt.l


$(parser): pt.y pt.h
	bison -b objs/pt -d pt.y



$(filter %.o, $(objects)): %.o: %.c
	$(cc) -c $(cflags) $< -o objs/$@





.PHONY: clean
clean:
	-rm objs/* bin/*


