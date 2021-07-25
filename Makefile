.PHONY: all_cli clean_cli run_cli all clean run doc

SRC = src/
OBJS = objs/
OBJECTS = board.o player.o game.o main.o
EXECUTABLE = othello.exe
SOURCE = source/

all_cli:
	cd $(SRC); make all; mv $(EXECUTABLE) ..;

run_cli:
	make all_cli; gnome-terminal --maximize -- ./$(EXECUTABLE); 

clean_cli:
	rm -f $(EXECUTABLE); cd $(OBJS); rm -f *.o;

all:
	cd $(SOURCE);make all;

run:
	cd $(SOURCE) ; make run;

clean:
	cd $(SOURCE); make clean;

all2:
	cd $(SOURCE);make all;

run2:
	cd $(SOURCE) ; make run;

clean2:
	cd $(SOURCE); make clean;

doc:
	doxygen Doxyfile;
	xdg-open ./documentation/html/index.html
