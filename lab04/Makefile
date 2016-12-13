all: bin ms_cli

bin:
	mkdir -p bin

ms_cli: bin/ms_cli.o bin/mergesort.o bin/comparator.o bin/str.o bin/mem.o
	gcc bin/ms_cli.o bin/mergesort.o bin/comparator.o bin/str.o bin/mem.o -o ms_cli

bin/ms_cli.o: src/ms_cli.c include/comparator.h include/mergesort.h include/str.h
	gcc -c src/ms_cli.c -o bin/ms_cli.o -I include/

bin/mergesort.o: src/mergesort.c include/str.h include/mem.h
	gcc -c src/mergesort.c -o bin/mergesort.o -I include/

bin/comparator.o: src/comparator.c include/str.h
	gcc -c src/comparator.c -o bin/comparator.o -I include/

bin/str.o: src/str.c
	gcc -c src/str.c -o bin/str.o

bin/mem.o: src/mem.c
	gcc -c src/mem.c -o bin/mem.o

clean:
	rm -rf bin
	rm -f ms_cli
