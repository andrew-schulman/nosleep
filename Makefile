#
# nosleep Makefile
#

SRC := nosleep.c windows.c
TGT := nosleep

CC      := gcc
CFLAGS  += -std=c99
LDFLAGS += -largp

windows.o : CFLAGS += -DWINVER=0x500


###############################


OBJ := $(SRC:.c=.o)

.PHONY: all check test install clean

all: $(TGT)

$(TGT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

check: test
test: $(TGT)
	cd test && make

install: $(TGT)
	mkdir -p $(DESTDIR)/usr/bin $(DESTDIR)/usr/share/man/man1 $(DESTDIR)/usr/share/doc/nosleep
	chmod 0644 *
	chmod 0755 $(TGT)
	cp $(TGT) $(DESTDIR)/usr/bin
	cp nosleep.1 $(DESTDIR)/usr/share/man/man1
	cp ChangeLog README $(DESTDIR)/usr/share/doc/nosleep

clean:
	rm -f $(TGT) *.o
