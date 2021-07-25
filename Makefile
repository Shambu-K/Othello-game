.PHONY: all_cli clean_cli run_cli all clean run doc

OBJECTS = board.o player.o game.o main.o
EXECUTABLE = othello.exe
SOURCE = source/

all_cli:
	cd $(SOURCE);make all;

run_cli:
	cd $(SOURCE) ; make run;

clean_cli:
	cd $(SOURCE); make clean;

all:
	cd $(SOURCE);make all;

run:
	cd $(SOURCE) ; make run;

clean:
	cd $(SOURCE); make clean;


doc:
	doxygen Doxyfile;
	xdg-open ./documentation/html/index.html
