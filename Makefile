TARGET = ruller
SRC_DIR = src
BUILD_DIR = build

SRC = $(SRC_DIR)/Globals.cxx \
      $(SRC_DIR)/Point.cxx \
      $(SRC_DIR)/main.cxx \
      $(SRC_DIR)/GUI.cxx \
      $(SRC_DIR)/DraggableImage.cxx \
      $(SRC_DIR)/Utils.cxx \
      $(SRC_DIR)/Callbacks.cxx

INCLUDES = -I$(SRC_DIR)

CXX = g++
CXXFLAGS = -std=gnu++17 $(INCLUDES)
LDFLAGS = -lfltk_images -lfltk -lpng -ljpeg -lz

OBJ = $(SRC:$(SRC_DIR)/%.cxx=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) $(TARGET) run

$(BUILD_DIR):
	@mkdir -p $@

$(TARGET): $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	@./$(TARGET)

clean:
	@rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all run clean