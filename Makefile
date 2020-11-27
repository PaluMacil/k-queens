# Reference: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I. 
DEBUGFLAGS=-Wall -Wextra -Wfloat-equal -Wpointer-arith -Wshadow -g
DEPS = 

.DEFAULT_GOAL := kq

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

kq: main.o eval.o
	$(CC) -o kq main.o eval.o

all: main.o eval.o
	$(CC) -o kq main.o eval.o

clean:
	rm *.o kq