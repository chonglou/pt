cc = gcc
#cc = clang
target = /usr/local/bin

cflags = -I. -lm

objects = main.o symlist.o nodes.o eval.o utils.o log.o message.o func.o
analyser = objs/pt.lex.c
parser = objs/pt.tab.c objs/pt.tab.h


all: pt


pt: $(analyser) $(objects)
	$(cc) -O2 -s $(cflags) -o bin/$@  objs/$@.tab.c ${analyser} $(addprefix objs/, $(objects))


$(analyser): $(parser) pt.h
	flex -o objs/pt.lex.c pt.l


$(parser): pt.y pt.h
	bison -b objs/pt -d pt.y



$(filter %.o, $(objects)): %.o: %.c
	$(cc) -c $(cflags) $< -o objs/$@


install: pt
	-cp pt $(target)/pt


uninstall:
	-rm $(target)/pt




.PHONY: clean
clean:
	-rm objs/* bin/*


