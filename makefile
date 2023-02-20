CC = gcc
CFLAGS = -I include
LDFLAGS = -L lib
LDLIBS = -lSDL2-2.0.0

sdl: sdl.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

.PHONY: clean
clean:
	rm -f sdl
