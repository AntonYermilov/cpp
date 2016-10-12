all: bin main

bin:
	mkdir -p bin/

clean:
	rm -rf bin/
	rm -f main
	rm -f src/*~
	rm -f include/*~

main: bin/main.o bin/position.o bin/clist.o
	gcc -g -o main bin/main.o bin/clist.o bin/position.o

bin/main.o: src/main.c include/position.h include/clist.h
	gcc -g -c -o bin/main.o src/main.c -I include/

bin/position.o: src/position.c include/position.h include/clist.h
	gcc -g -c -o bin/position.o src/position.c -I include/

bin/clist.o: src/clist.c include/clist.h
	gcc -g -c -o bin/clist.o src/clist.c -I include/
