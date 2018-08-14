LDLIBS = ../liblbs.a
LBS_INCLUDE_DIR = ../include

all: mylualib.so

mylualib.so: mylualib.o ../liblbs.a
	$(CC) $(LDFLAGS) -shared -o "$@" $< $(LDLIBS)

clean:
	rm -rf mylualib.so mylualib.o

.PHONY: all clean
