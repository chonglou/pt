cc = g++

all: pt


pt: pt.l pt.yy ctx.hh utils.hh utils.cc
	bison -b objs/$@ -d pt.yy
	flex -o objs/$@.yy.c pt.l
	$(cc) -O2 -s -I. -o bin/$@  objs/$@.yy.c objs/$@.tab.cc utils.cc



clean:
	-rm objs/* bin/*


