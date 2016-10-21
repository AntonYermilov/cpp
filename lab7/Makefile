.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -g

all: main

bin:
	mkdir -p bin

main: src/main.cpp bin/my_vector.o include/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -I include $< bin/*

bin/%.o: src/%.cpp include/*.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ -I include $<

clean:
	rm -rf bin main
