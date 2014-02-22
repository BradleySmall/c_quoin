##
## Author: Bradley M. Small
## Copyright (c) 2014 All rights reserver
##
## Generic Makefile for development
##
DEPS=$(wildcard Makefile *.h)
SRCS=$(wildcard *.c)
BIN=$(shell grep -l main *.c* | cut -d'.' -f1).bin

OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Wall -Wextra

all : $(BIN)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(BIN) : $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 

clean :
	rm -rf $(OBJS) $(BIN) *~

