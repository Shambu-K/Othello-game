CXX = g++-10 -std=c++20
CXXFLAGS = -g -Wall -Werror -pedantic -pedantic-errors
SOURCES = Controller/controller.cpp Model/board.cpp View/*.cpp
INCLUDE = ./ Controller/ Model/ View/ AI/
TARGET = Othello
FLAGS = -ltgui -lsfml-graphics -lsfml-window -lsfml-system

all:
	$(CXX) -g -Wall -Werror -pedantic -pedantic-errors $(SOURCES) -I ./ -I Controller/ -I View/ -I Model/ -o $(TARGET) $(FLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
