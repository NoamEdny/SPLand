# שם הקומפיילר
CXX = g++

# דגלים לקומפילציה
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# תיקיות
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# קבצים
TARGET = $(BIN_DIR)/simulation_test
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# כלל ברירת מחדל
all: $(TARGET)

# בניית הקובץ הבינארי
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# קומפילציה של קבצי ה-CPP
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# יצירת תיקיות אם לא קיימות
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ניקוי קבצים
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# הרצה של הסימולציה
run: all
	$(TARGET) config_file.txt
