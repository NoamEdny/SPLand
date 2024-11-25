# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Target executable
TARGET = settlement_test

# Source files and objects
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default rule to build the project
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
