# Makefile for Beginning Linux Programming 3rd Edition
# Chapter 3

SIMPLE=simple_write simple_read
COPY=copy_system copy_block copy_stdio copy_stdio2
ICTC_COPY=ictc_copy1 ictc_copy2
DIR=printdir printdir2
MMAP=mmap

ALL= $(SIMPLE) $(COPY) $(DIR) $(MMAP) $(ICTC_COPY)

all: $(ALL)

clean:
	@rm -f $(ALL) file.out records.dat *~
