# Makefile baseline provided by assignment, adjustments made as necessary
CC = g++
#CLASSDIR = /home/huangj/cs360
#CDIR = /home/cs360
#INCLUDES = $(CLASSDIR)/include
CFLAGS = -Wall -g #-I$(INCLUDES)
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
	$(CC) $(CFLAGS) -c fields.c

entities.o:
	$(CC) $(CFLAGS) -c entities.cpp

#handler.o:
#	$(CC) $(CFLAGS) -c handler.cpp

master: main.o fields.o entities.o
	$(CC) -o master main.o fields.o entities.o

#master: main.o fields.o entities.o handler.o
#	$(CC) -o master main.o fields.o entities.o handler.o
