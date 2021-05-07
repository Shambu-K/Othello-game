.PHONY: clean run

CXX = g++-10
CXXFLAGS = -std=c++20  #-Wall -Werror -pedantic -pedantic-errors
FMTFLAG = -lfmt -lcurses
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
