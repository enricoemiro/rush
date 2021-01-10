CC=g++
SRC=src
OBJ=obj
CPPFLAGS=-g -Wall
LDLIBS=-lncurses

# Find all .cpp files
SRCS=$(shell find -name '*.cpp')

# Replace .cpp with .o
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

# Name of the binary file to generate
BIN=game

# Default command
all: $(OBJ) $(BIN)

# Create the executable
$(BIN): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Create object files
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

# If it doesn't exist make the object folder
$(OBJ):
	mkdir -p $@

# Delete all generated files
clean:
	rm -rf $(OBJ) $(BIN)

.PHONY: all clean $(OBJ)
