.PHONY: clean run

SRC = src/
OBJS = objs/
OBJECTS = board.o player.o game.o main.o
EXECUTABLE = othello.exe

all:
	cd $(SRC); make; mv $(EXECUTABLE) ..; mv $(OBJECTS) ../objs/;

run:
	make all; ./$(EXECUTABLE); 

clean:
	rm $(EXECUTABLE); cd $(OBJS); rm *.o;
