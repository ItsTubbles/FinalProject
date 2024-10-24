CXX = g++
CXXFLAGS = -g -Wall -std=gnu++11
LIBS = -lncurses
SHELL = bash

# Source files
SRC = Main.cpp Tetris.cpp

# Output binary
TARGET = tetris

# Rule to build the target (executable)
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Clean up rule to remove the executable
clean:
	rm -f $(TARGET)

# PHONY targets
.PHONY: clean
