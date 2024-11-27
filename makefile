# Compiler and flags
CXX = g++
CXXFLAGS = -g -Wall -Weffc++ -std=c++17 -Iinclude

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Target program
TARGET = $(BINDIR)/program

# Source and object files
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/Settlement.cpp $(SRCDIR)/Facility.cpp \
       $(SRCDIR)/SelectionPolicy.cpp $(SRCDIR)/Plan.cpp
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Link the program
$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR) $(BINDIR)

# Phony targets
.PHONY: all clean
