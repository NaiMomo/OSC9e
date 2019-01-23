

AS=as
OUTPUT=chdir-example data_allocation exec exec_ls execvpe-example fork fork-copy stack_allocation sys_getcwd_main

all: ${OUTPUT}

clean-object:
	rm *.o

clean:
	rm -f ${OUTPUT} *.o

chdir-example: chdir-example.o

data_allocation: data_allocation.o

exec: exec.o

exec_ls: exec_ls.o

execvpe-example: execvpe-example.o

fork: fork.o

fork-copy: fork-copy.o

stack_allocation: stack_allocation.o

sys_getcwd_main: sys_getcwd_main.o os_getcwd.o

os_getcwd.o: os_getcwd.asm


.SUFFIXES:
.SUFFIXES: .asm .o .c
.asm.o:
	as -o $@ $<

.PHONY:
.PHONY: all clean clean-object


