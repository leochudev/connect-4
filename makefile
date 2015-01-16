CC=g++
CFLAGS=-c -std=c++11 -Wall
LDFLAGS=
SOURCES=main.cpp lib/game.cpp lib/gameBoard.cpp lib/gamePlayer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=connect4

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@