.PHONY: clean run

SRC = src/
OBJS = objs/
OBJECTS = board.o player.o game.o main.o
EXECUTABLE = othello.exe

all:
	cd $(SRC); make all; mv $(EXECUTABLE) ..; mv $(OBJECTS) ../objs/;

run:
	make all; gnome-terminal --maximize -- ./$(EXECUTABLE); 

clean:
	rm -f $(EXECUTABLE); cd $(OBJS); rm -f *.o;
