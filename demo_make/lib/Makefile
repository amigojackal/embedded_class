all: libfoo.so

libfoo.so: libfoo.o
	$(CC) -shared -o $@ $^
clean:
	-rm -f *.so *.o
	@echo "removing library"
