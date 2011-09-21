#
# Makefile for nosleep
#

SRC := nosleep.c
TGT := nosleep

CC := gcc
CFLAGS := -DWINVER=0x500
LDFLAGS :=

OBJ := $(SRC:.c=.o)

$(TGT): $(SRC)

.PHONY: clean
clean:
	rm -f $(TGT) *.o
