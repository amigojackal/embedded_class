all: libfoo.so

libfoo.so: libfoo.o
	$(CC) -shared -o libfoo.so $^
clean:
	-rm -f *.so
