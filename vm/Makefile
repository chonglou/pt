cc = g++

all: pt


pt: ctx.hh pt.l pt.yy
	bison -b objs/$@ -d $@.yy
	flex -o objs/$@.yy.c $@.l
	$(cc) -s -I. -o bin/$@  objs/$@.yy.c objs/$@.tab.cc



clean:
	-rm objs/* bin/*


