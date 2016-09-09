all: main.o algorithm.o util.o io.o
	gcc -o lab1 bin/io.o bin/util.o bin/algorithm.o bin/main.o

main.o: src/main.c
	gcc -c -o bin/main.o src/main.c

algorithm.o: src/algorithm.c include/algorithm.h
	gcc -c -o bin/algorithm.o src/algorithm.c -I include/

util.o: src/util.c include/util.h
	gcc -c -o bin/util.o src/util.c -I include/

io.o: src/io.c include/io.h
	gcc -c -o bin/io.o src/io.c -I include/

clean:
	rm -f bin/*.o
	rm -f lab1
