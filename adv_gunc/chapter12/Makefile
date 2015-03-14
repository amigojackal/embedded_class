TARGET = thread1 thread2 thread2c thread3 thread3a thread4 thread4a thread5 thread6 thread7 thread8 thread8a

all: $(TARGET)
	@echo $(TARGET:=.c)


$(TARGET): $(TARGET:=.c)
	$(CC)  $(CFLAGS) $@.c $(LDFLAGS) -o $@

CFLAGS=-I/usr/include/nptl -D_REENTRANT
LDFLAGS=-L/usr/lib/nptl -lpthread

clean:
	rm -f thread1 thread2 thread3 thread3a thread4 thread5 thread6 thread7 thread7a thread8 thread8a


