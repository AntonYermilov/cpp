CXX = g++
CXXFLAGS = -O3 -pedantic -Wall -Wextra -Werror -Iinclude -std=c++11
OBJECTS = $(patsubst src/%.cpp, bin/%.o, $(wildcard src/*.cpp))
EXE = huffman

all: $(EXE)

$(EXE): bin $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)

bin/%.o: src/%.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin:
	mkdir -p bin

clean:
	rm -rf bin $(EXE)

