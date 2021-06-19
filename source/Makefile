CXX = g++
SOURCES = Controller/controller.cpp Model/board.cpp View/*.cpp
INCLUDE = ./ Controller/ Model/ View/
TARGET = Othello
FLAGS = -ltgui -lsfml-graphics -lsfml-window -lsfml-system -lfmt

all:
	$(CXX) $(SOURCES) -I ./ -I Controller/ -I View/ -I Model/ -o $(TARGET) $(FLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
