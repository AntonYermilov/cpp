all: create_dir lab1

lab1: bin/main.o bin/algorithm.o bin/util.o bin/io.o
	gcc -o lab1 bin/io.o bin/util.o bin/algorithm.o bin/main.o

create_dir:
	mkdir -p bin/

bin/main.o: src/main.c include/algorithm.h include/util.h include/io.h
	gcc -c -o bin/main.o src/main.c

bin/algorithm.o: src/algorithm.c include/algorithm.h include/util.h include/io.h
	gcc -c -o bin/algorithm.o src/algorithm.c -I include/

bin/util.o: src/util.c include/util.h include/io.h
	gcc -c -o bin/util.o src/util.c -I include/

bin/io.o: src/io.c include/io.h
	gcc -c -o bin/io.o src/io.c -I include/

clean:
	rm -rf bin
	rm -f lab1
