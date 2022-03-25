CC = gcc
AR = ar
FLAGS = -Wall -g

OBJECTS_Shell = Shell.o
OBJECTS_Server =  Server.o
SOURCES = Shell.c, Server.c

all: Server Shell

Server: $(OBJECTS_Server)
	$(CC) $(FLAGS) -o Server $(OBJECTS_Server)

Shell: $(OBJECTS_Shell) lib_shell.a
	$(CC) $(FLAGS) -o Shell $(OBJECTS_Shell) lib_shell.a 

#Make commands as singles:

lib_shell.a: $(OBJECTS_Shell) #static library for shell
	$(AR) -rcs lib_shell.a $(OBJECTS_Shell)

Shell.o: Shell.c Shell.h
	$(CC) $(FLAGS) -c Shell.c


.PHONY: clean all

clean:
	rm -f *.o *.so Shell Server lib_shell.a

