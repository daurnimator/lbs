MAJOR := 0
MINOR := 1
VERSION := $(MAJOR).$(MINOR)

INCLUDE_DIR = include/
INCLUDE_FILES = $(wildcard include/*)

CPPFLAGS += -I$(INCLUDE_DIR)

C_FILES = src/lbs.c \
	src/types.c
O_FILES = $(patsubst %.c, %.o, $(C_FILES))

all: static shared

static: liblbs.a

liblbs.a: $(O_FILES)
	ar rc "$@" $^

shared: liblbs.so

liblbs.so.$(VERSION): $(O_FILES)
	$(CC) $(LDFLAGS) -shared -Wl,-soname,liblbs.so.$(MAJOR) -o "$@" $^

liblbs.so.$(MAJOR): liblbs.so.$(VERSION)
	ldconfig -v -n .

liblbs.so: liblbs.so.$(MAJOR)
	ln -s liblbs.so.$(MAJOR) liblbs.so

example: liblbs.a
	$(MAKE) -C examples CPPFLAGS="$(CPPFLAGS) -I../include/" LDFLAGS="$(LDFLAGS) -L../"

clean:
	rm -rf liblbs.a \
		liblbs.so liblbs.so.$(MAJOR) liblbs.so.$(VERSION) \
		$(O_FILES)
	$(MAKE) -C examples "$@"

.PHONY: all static shared clean
