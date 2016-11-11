CC     = gcc
CFLAGS = -std=c99 -Wall -Wextra

all: main

bin:
	mkdir -p bin

main: bin bin/main.o bin/bmp.o include/*.h
	$(CC) $(CFLAGS) -o $@ -I include bin/main.o bin/bmp.o

bin/%.o: src/%.c include/*.h
	$(CC) $(CFLAGS) -c -o $@ -I include $<

clean:
	rm -rf bin main
