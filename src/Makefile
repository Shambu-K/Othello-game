.PHONY: clean run

INCLUDE = ../lib/include
LIB = ../lib
CXX = g++-10
CXXFLAGS = -std=c++20 -L $(LIB) -I $(INCLUDE) #-Wall -Werror -pedantic -pedantic-errors
FMTFLAG = -lfmt
SOURCES = board.cpp player.cpp game.cpp main.cpp
OBJECTS = board.o player.o game.o main.o
EXECUTABLE = othello.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(FMTFLAG)

.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)


run:
	./$(EXECUTABLE)
