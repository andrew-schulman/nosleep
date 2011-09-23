#
# nosleep Makefile
#

SRC := nosleep.c windows.c
TGT := nosleep

CC := gcc
CFLAGS  :=
LDFLAGS := -largp

windows.o : CFLAGS += -DWINVER=0x500


###############################


OBJ := $(SRC:.c=.o)

all: $(TGT)

$(TGT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(TGT) *.o
