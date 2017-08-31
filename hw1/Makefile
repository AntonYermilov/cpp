CC     = gcc
CFLAGS = -std=c99 -Wall -Wextra -I include

all: main

bin:
	mkdir -p bin

main: bin bin/main.o bin/bmp.o include/*.h
	$(CC) $(CFLAGS) -o $@ bin/main.o bin/bmp.o

bin/%.o: src/%.c include/*.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf bin main
