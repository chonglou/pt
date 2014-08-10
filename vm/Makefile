
objects = main.o command.o display.o log.o
cc = clang


#all:
#	echo ''



#vm: $(objects)
#	cc -o pt $(objects)


#$(filter %.o, $(objects)): %.o: %.c %.h
#	$(CC) -c $(CFLAGS) $< -o $@

#-------------tools
tools = count calculator

$(filter %, $(tools)): %: src/tools/%.l
	#bison -b objs/$@ -d src/tools/$@.y
	flex -o objs/$@.yy.c src/tools/$@.l
	$(cc) -o bin/$@ -lfl objs/$@.yy.c


#-------------others
.PHONY: clean
clean:
	--rm pt $(objects)


