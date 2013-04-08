CC=g++
INCDIR=include/
CFLAGS=-c -Wall -I$(INCDIR)
LDFLAGS=-lGL -lGLU -lsfml-system -lsfml-window
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=SubdivisionSurfaces

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) -O2 -flto

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -O2 -flto

clean:
	rm $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean
