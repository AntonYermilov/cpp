all: main

main: bin bin/main.o
	g++ bin/main.o -o main

bin/main.o: src/main.cpp include/my_array.h
	g++ -std=c++11 -pedantic -Wall -Wextra -Werror -c src/main.cpp -o bin/main.o -Iinclude

bin:
	mkdir -p bin

clean:
	rm -rf bin main


