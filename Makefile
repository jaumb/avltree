#
# makefile for avl tree class file
WFLAGS = -Werror -Wall -Wextra \
		-Wno-uninitialized -Wshadow

# This is a c++ project
CC  = g++

# Use c++ version 11
CCFLAGS = $(WFLAGS)
INC = inc
SRC = src
LIB = lib

avltree.o: $(INC)/avltree.h $(INC)/avltreetemplates.h
	$(CC) $(CCFLAGS) -I$(INC) -c -o $(LIB)/avltree.o \
	    $(SRC)/avltree.cc

clean:
	rm -f $(LIB)/*.o

