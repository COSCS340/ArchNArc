# Makefile baseline provided by assignment, adjustments made as necessary
CC = g++
#CLASSDIR = /home/huangj/cs360
#CDIR = /home/cs360
#INCLUDES = $(CLASSDIR)/include
CFLAGS = -Wall -g -I#$(INCLUDES)
#LIBDIR = $(CDIR)/pub
#LIBS = $(LIBDIR)/libfdr.a
EXECUTABLES = master

all: $(EXECUTABLES)

clean:
	rm -f core $(EXECUTABLES) *.o

.SUFFIXES: .c .o
main.o:
	$(CC) $(CFLAGS) -c main.cpp

fields.o:
	$(CC) $(CGLAGS) -c fields.c

master: main.o
	$(CC) -o master main.o fields.o

#master: main.o
#	$(CC) -g -o test_malloc malloc.o test_malloc.o $(LIBS)
