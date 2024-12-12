# Makefile
CC=gcc
CFLAGS= -g -W -Wall 
LDFLAGS = 
OBJ = lib.o test.o

test : $(OBJ)
		$(CC) $(OBJ) -o test

test : test.c lib.h

lib.o : lib.c

clean :
		rm -rf $(OBJ) main
