#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <CommandHandler.hpp>

#define BUFFER_SIZE 1024
#define COMMAND_CHANNEL_PORT 9009
#define DATA_CHANNEL_PORT 9099
#define RUNNING 1
#define RECIEVEING 1

int run_socket(int port);

int main() {
    int command_fd = run_socket(COMMAND_CHANNEL_PORT);
    int data_fd = run_socket(DATA_CHANNEL_PORT);

    struct sockaddr_in address;

    char buffer[BUFFER_SIZE];

    while(RUNNING) {
        int client_fd;
        int addr_len = sizeof(address);
        printf("Wainting for connection...\n");
        
        //accepting a new connection
        if(!(client_fd = accept(command_fd, (struct sockaddr*) &address, (socklen_t*) &addr_len))) {
            printf("Couldn't accept the client!\n");
            continue;
        }

        printf("Successfully connected to a client!\n");  

        while(RECIEVEING) {
            recv(client_fd, buffer, BUFFER_SIZE, 0);
            CommandHandler *command_handler = new CommandHandler(client_fd, buffer);
            command_handler -> run_command();

        }

        close(client_fd);
    }
    close(command_fd);
    close(data_fd);
    return 0;
}

int run_socket(int port) {
    //declaring important data
    int fd;
    struct sockaddr_in address;
    
    //Creating a socket
    if(!(fd = socket(AF_INET, SOCK_STREAM, 0))) {
        printf("Failed to create socket on port %d!\nExiting..", port);
        exit(1);
    }

    //Assigning attributes to address
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Binding the socket 
    if ((bind(fd, (struct sockaddr*) &address, sizeof(address))) < 0) {
        printf("Failed to bind the connection!\nExiting..\n");
        exit(1);
    }

    //Listening on the server
    if((listen(fd, 10)) < 0) {
        printf("Failed to listen!\nExiting..\n");
        exit(1);
    }

    return fd;
}