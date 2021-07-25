.PHONY: all_cli clean_cli run_cli all clean run doc

OBJECTS = board.o player.o game.o main.o
EXECUTABLE = othello.exe
SOURCE = source/
SOURCE2 = source2/

all_cli:
	cd $(SOURCE2);make all;

run_cli:
	cd $(SOURCE2) ; make run;

clean_cli:
	cd $(SOURCE2); make clean;

all:
	cd $(SOURCE);make all;

run:
	cd $(SOURCE) ; make run;

clean:
	cd $(SOURCE); make clean;


doc:
	doxygen Doxyfile;
	xdg-open ./documentation/html/index.html
