
FMTDIR = /home/rivak/packages/fmt
INCLUDEDIR = $(FMTDIR)/include

CXX = g++-10 -std=c++20
CXXFLAGS = -g -Wall -Werror -pedantic -pedantic-errors -I $(INCLUDEDIR) -I $(INCLUDE)
SOURCES = Controller/controller.cpp Model/board.cpp View/*.cpp
OBJS = controller.o board.o game_play_cli.o title_page_cli.o
INCLUDE = ./
TARGET = Othello
FLAGS = -lfmt

.PHONY = all run clean

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -L $(FMTDIR) -o $(TARGET) $(FLAGS)

controller.o : Controller/controller.cpp Controller/controller.h
	$(CXX) $(CXXFLAGS) -c $<
board.o : Model/board.cpp Model/board.h
	$(CXX) $(CXXFLAGS) -c $<  

game_play_cli.o : View/game_play_cli.cpp View/game_play_cli.h
	$(CXX) $(CXXFLAGS) -c $<  

title_page_cli.o : View/title_page_cli.cpp
	$(CXX) $(CXXFLAGS) -c $< 

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
