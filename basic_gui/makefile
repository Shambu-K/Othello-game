.PHONY: clean run debug

CXX = g++
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SOURCES = trial3.cpp
OBJECTS = trial3.o
EXECUTABLE = trial3.exe

all: $(EXECUTABLE) run


$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(SFMLFLAGS)

trial3.o:trial3.cpp
	$(CXX) -c trial3.cpp

clean:
	rm -f $(EXECUTABLE);rm -f $(OBJECTS) 

debug:
	$(CXX) -g -o debug.exe $(SOURCES)

run :
	./$(EXECUTABLE)