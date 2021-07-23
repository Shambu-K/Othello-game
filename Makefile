.PHONY: clean_cli run_cli clean_gui run_gui

SRC = src/
OBJS = objs/
OBJECTS = board.o player.o game.o main.o
EXECUTABLE = othello.exe
SOURCE = source/

all_cli:
	cd $(SRC); make all; mv $(EXECUTABLE) ..; mv $(OBJECTS) ../objs/;

run_cli:
	make all_cli; gnome-terminal --maximize -- ./$(EXECUTABLE); 

clean_cli:
	rm -f $(EXECUTABLE); cd $(OBJS); rm -f *.o;

all_gui:
	cd $(SOURCE);make all;

run_gui:
	cd $(SOURCE) ; make run;

clean_gui:
	cd $(SOURCE); make clean;
