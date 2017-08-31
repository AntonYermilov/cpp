CXX = g++
CXXFLAGS = -O3 -pedantic -Wall -Wextra -Iinclude -std=c++14 -D_GLIBCXX_DEBUG #-fsanitize=undefined
OBJECTS = $(patsubst src/%.cpp, bin/%.o, $(wildcard src/*.cpp))
EXE = main

all: $(EXE)

$(EXE): bin $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)

bin/%.o: src/%.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin:
	mkdir -p bin

clean:
	rm -rf bin $(EXE)

