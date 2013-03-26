CC=g++
INCDIR=include/
CFLAGS=-c -Wall -ggdb -I$(INCDIR)
LDFLAGS=-lGL -lsfml-system -lsfml-window
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=SubdivisionSurfaces

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all
