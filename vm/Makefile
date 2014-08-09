
objects = main.o command.o display.o log.o


all:
	echo ''



vm: $(objects)
	cc -o pt $(objects)


$(filter %.o, $(objects)): %.o: %.c %.h
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: clean
clean:
	--rm pt $(objects)


