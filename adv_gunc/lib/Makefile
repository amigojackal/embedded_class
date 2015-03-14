OBJS= net.o socket.o tinydns.o
all:libgg.a

libgg.a: $(OBJS)
	$(AR) cr libgg.a $(OBJS)
clean:
	rm *\.o libgg.a -f
