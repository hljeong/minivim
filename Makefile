CC = g++
CFLAGS = -Wall -g -std=c++17 -I lib
LIBS = -lncurses

SRC_PATH = src
OBJ_PATH = obj
SRC_FILES = main.cpp \
            minivim.cpp \
            buffer.cpp \
            console.cpp
OBJ_FILES = $(SRC_FILES:%.cpp=%.o)
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_FILES))

TARGET = minivim

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) 2>/dev/null

clean: 
	rm -rf $(OBJ_PATH)
	rm -rf $(TARGET)
