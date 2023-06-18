# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -Wall -I./include

# Target executables
TARGET_SERVER = chat_server
TARGET_CLIENT = chat_client

# Folders
SRC_DIR = ./src
BIN_DIR = ./bin
OBJ_DIR = ./build

# Sources and Objects
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: directories $(BIN_DIR)/$(TARGET_SERVER) $(BIN_DIR)/$(TARGET_CLIENT)

$(BIN_DIR)/$(TARGET_SERVER): $(OBJ_DIR)/$(TARGET_SERVER).o
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/$(TARGET_CLIENT): $(OBJ_DIR)/$(TARGET_CLIENT).o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: directories

directories:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(BIN_DIR)/$(TARGET_SERVER) $(BIN_DIR)/$(TARGET_CLIENT) $(OBJ_DIR)/*.o
