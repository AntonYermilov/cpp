all: bin lab2

bin:
	mkdir -p bin/

lab2: bin/test.o bin/test_str.o bin/str.o
	gcc -o lab2 bin/test.o bin/test_str.o bin/str.o

bin/test.o: src/test.c include/test_str.h
	gcc -c -o bin/test.o src/test.c -I include/

bin/test_str.o: src/test_str.c include/test_str.h include/str.h
	gcc -c -o bin/test_str.o src/test_str.c -I include/

bin/str.o: src/str.c include/str.h
	gcc -c -o bin/str.o src/str.c -I include/

clean:
	rm -rf bin/
	rm -f lab2
