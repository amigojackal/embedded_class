
all: dbm1 dbm2 lock1 lock2 lock3 lock4 lock5 memory1 memory2 memory3 memory4 memory5a memory5b memory6

INCLUDE=/usr/include/gdbm
LIBS=-lgdbm
# On some systems you may have to change the line above to include the
# compatability library, as shown below
# LIBS=-lgdbm -lgdbm_compat


dbm1: dbm1.c
	gcc -I$(INCLUDE) $< -o $@ $(LIBS)

dbm2: dbm2.c
	gcc -I$(INCLUDE) $< -o $@ $(LIBS)


clean:
	rm dbm1 dbm2 lock1 lock2 lock3 lock4 lock5 memory1 memory2 memory3 memory4 memory5a memory5b memory6


