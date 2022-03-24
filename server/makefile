CC = g++
BUILD_DIR = build
SRC_DIR = src
HEADERS_DIR = headers
CFLAGS = -std=c++17 -pthread -Wall -Werror -I$(HEADERS_DIR)

TARGET = server.out

OBJECTS = \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/CommandHandler.o

CommandHandlerDeps = $(SRC_DIR)/CommandHandler.cpp \
	$(HEADERS_DIR)/CommandHandler.hpp

ServerDeps = $(SRC_DIR)/server.cpp \
	$(HEADERS_DIR)/CommandHandler.hpp

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/server.o: $(ServerDeps)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/server.o	

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerDeps)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
