SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
ELF:=sever
CC:=gcc
CFLAGS:=-g -Wall
$(ELF):$(OBJS)
	gcc -o $@ $^
clean:
	rm -rf $(OBJS) $(ELF)
