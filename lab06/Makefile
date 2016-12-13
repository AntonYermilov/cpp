all: bin main

bin:
	mkdir -p bin

main: bin/main.o bin/phonebook.o
	gcc -g -I include -o main bin/main.o bin/phonebook.o -lexpat

bin/main.o: src/main.c include/*.h
	gcc -g -c -I include -o bin/main.o src/main.c

bin/phonebook.o: src/phonebook.c include/*.h
	gcc -g -c -I include -o bin/phonebook.o src/phonebook.c

clean:
	rm -rf bin main
	rm -f src/*~
	rm -f include/*~
