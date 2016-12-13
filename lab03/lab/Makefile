all: bin pose_db

pose_db: bin/main.o bin/clist.o
	gcc -ggdb3 -o pose_db bin/main.o bin/clist.o

bin:
	mkdir -p bin/

clean:
	rm -rf bin/
	rm -f pose_db

bin/main.o: src/main.c include/clist.h
	gcc -ggdb3 -c -o bin/main.o src/main.c -I include/


bin/clist.o: src/clist.c include/clist.h
	gcc -ggdb3 -c -o bin/clist.o src/clist.c -I include/



