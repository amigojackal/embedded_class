all: libfoo
	$(CC) -Iinc -o main main.c -Llib -lfoo


#all: libfoo main

libfoo:
	make -C lib

clean:
	-rm -f main
	make -C lib
