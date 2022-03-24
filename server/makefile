CC = g++
BUILD_DIR = build
SRC_DIR = src
HEADERS_DIR = headers
CFLAGS = -std=c++17 -pthread -Wall -Werror -I$(HEADERS_DIR)

TARGET = server

OBJECTS = \
	$(BUILD_DIR)/Server.o \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/UserHandler.o \
	$(BUILD_DIR)/ConfigParser.o \
	$(BUILD_DIR)/Exception.o \
	$(BUILD_DIR)/main.o

ConfigParserDeppendencies = $(SRC_DIR)/ConfigParser.cpp \
	$(HEADERS_DIR)/ConfigParser.hpp \
	$(HEADERS_DIR)/Json.hpp \
	$(HEADERS_DIR)/User.hpp

UserDeppendencies = $(SRC_DIR)/User.cpp \
	$(HEADERS_DIR)/User.hpp

ExceptionDeppendencies = $(SRC_DIR)/Exception.cpp \
	$(HEADERS_DIR)/Exception.hpp

UserHandlerDeppendencies = $(SRC_DIR)/UserHandler.cpp \
	$(HEADERS_DIR)/UserHandler.hpp \
	$(HEADERS_DIR)/Exception.hpp

CommandHandlerDeppendencies = $(SRC_DIR)/CommandHandler.cpp \
	$(HEADERS_DIR)/CommandHandler.hpp \
	$(HEADERS_DIR)/User.hpp

ServerDeppendencies = $(SRC_DIR)/server.cpp \
	$(HEADERS_DIR)/Server.hpp \
	$(HEADERS_DIR)/CommandHandler.hpp \
	$(HEADERS_DIR)/User.hpp 

MainDeppendencies = $(SRC_DIR)/main.cpp \
	$(HEADERS_DIR)/Server.hpp \
	$(HEADERS_DIR)/User.hpp \
	$(HEADERS_DIR)/UserHandler.hpp \
	$(HEADERS_DIR)/ConfigParser.hpp



all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: $(MainDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Server.o: $(ServerDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o	

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/User.o: $(UserDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UserHandler.o: $(UserHandlerDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UserHandler.cpp -o $(BUILD_DIR)/UserHandler.o

$(BUILD_DIR)/ConfigParser.o: $(ConfigParserDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ConfigParser.cpp -o $(BUILD_DIR)/ConfigParser.o	

$(BUILD_DIR)/Exception.o: $(ExceptionDeppendencies)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Exception.cpp -o $(BUILD_DIR)/Exception.o	

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
