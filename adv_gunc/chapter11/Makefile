# Makefile for Beginning Linux Programming 3rd Edition
# Chapter 11

ICTC_FORK=ictc_fork1 ictc_fork2 fork_fd1
SYSTEM=system1 system2 pexec pexec2 pexec3 mysystem
FORK=fork1 wait fork2 fork3 fork4 fork5
FILTER=upper useupper
SIGNALS=ctrlc1 alarm ctrlc2
EXEC=show_args exec_show_args pexec1 
ICTC_FORK_EXEC=fork_exec1 fork_exec2 fork_exec3 fork_copy_tar
CFLAGS=-g
LDFLAGS=-g

ALL= $(SYSTEM) $(FORK) $(FILTER) $(SIGNALS) $(ICTC_FORK) $(ICTC_FORK_EXEC)
all: $(ALL)
clean:
	@rm -f $(ALL) *~ *.o
