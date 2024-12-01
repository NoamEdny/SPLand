# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Weffc++ -std=c++11 -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/main

# Source files
SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/Simulation.cpp \
       $(SRC_DIR)/Action.cpp \
       $(SRC_DIR)/Auxiliary.cpp \
       $(SRC_DIR)/SelectionPolicy.cpp \
       $(SRC_DIR)/Facility.cpp \
       $(SRC_DIR)/Settlement.cpp \
       $(SRC_DIR)/Plan.cpp  # הוספתי את Plan.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# All target
all: clean bin $(TARGET)

# Clean target
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)

# Create bin directory
bin:
	mkdir -p $(BIN_DIR)

# Compile all .cpp files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Link object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run the executable
run: $(TARGET)
	./$(TARGET)

