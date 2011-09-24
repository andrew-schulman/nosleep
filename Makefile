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

.PHONY: clean install

install: $(TGT)
	mkdir -p $(DESTDIR)/usr/bin $(DESTDIR)/usr/share/man/man1 $(DESTDIR)/usr/share/doc/nosleep $(DESTDIR)/usr/share/doc/Cygwin
	chmod 0644 *
	chmod 0755 $(TGT)
	cp $(TGT) $(DESTDIR)/usr/bin
	cp nosleep.1 $(DESTDIR)/usr/share/man/man1
	cp ChangeLog README $(DESTDIR)/usr/share/doc/nosleep
	cp -f CYGWIN-PATCHES/README $(DESTDIR)/usr/share/doc/nosleep/README.Cygwin

clean:
	rm -f $(TGT) *.o
