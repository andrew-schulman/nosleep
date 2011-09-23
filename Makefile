#
# nosleep Makefile
#

SRC := nosleep.c windows.c
TGT := nosleep

CC := gcc
CFLAGS  := -DWINVER=0x500
LDFLAGS := -largp


###############################


OBJ := $(SRC:.c=.o)

all: $(TGT)

$(TGT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TGT) *.o
