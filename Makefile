CC=g++

CPPFLAGS += -std=c++11
CFLAGS = -g -Wall 
LDFLAGS =
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system 


SRC_DIR=src
BUILD_DIR=build
BIN_DIR=bin

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS=$(OBJECTS:.o=.d)

EXECUTABLE=percol


all: dirs $(BIN_DIR)/$(EXECUTABLE) 

$(BIN_DIR)/$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) $(CPPFLAGS) $(CFLAGS) -MP -MMD -c $< -o $@


.PHONY: dirs
dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

.PHONY: clean
clean:
	@rm -r $(BUILD_DIR) $(BIN_DIR)

