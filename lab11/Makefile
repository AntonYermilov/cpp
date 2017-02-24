CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -Iinclude -std=c++03
OBJECTS = $(patsubst src/%.cpp, bin/%.o, $(wildcard src/*.cpp))
EXE = empl_db

all: $(EXE)

$(EXE): bin $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE)

bin/%.o: src/%.cpp include/*.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

bin:
	mkdir -p bin

clean:
	rm -rf bin $(EXE)
	rm -f *~ */*~
