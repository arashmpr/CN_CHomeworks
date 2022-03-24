CC = g++
BUILD_DIR = build
SRC_DIR = src
HEADERS_DIR = headers
CFLAGS = -std=c++17 -pthread -Wall -Werror -I$(HEADERS_DIR)

TARGET = server.out

OBJECTS = \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/ConfigParser.o

ConfigParserDeppendencies = $(SRC_DIR)/ConfigParser.cpp \
	$(HEADERS_DIR)/ConfigParser.hpp \
	$(HEADERS_DIR)/Json.hpp \
	$(HEADERS_DIR)/User.hpp

UserDeppendencies = $(SRC_DIR)/User.cpp \
	$(HEADERS_DIR)/User.hpp

CommandHandlerDeppendencies = $(SRC_DIR)/CommandHandler.cpp \
	$(HEADERS_DIR)/CommandHandler.hpp \
	$(HEADERS_DIR)/User.hpp

ServerDeppendencies = $(SRC_DIR)/server.cpp \
	$(HEADERS_DIR)/CommandHandler.hpp \
	$(HEADERS_DIR)/User.hpp \
	$(HEADERS_DIR)/ConfigParser.hpp

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/server.o: $(ServerDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/server.o	

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/User.o: $(UserDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/ConfigParser.o: $(ConfigParserDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ConfigParser.cpp -o $(BUILD_DIR)/ConfigParser.o	

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
