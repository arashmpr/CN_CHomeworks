#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define COMMAND_CHANNEL_PORT 9009
#define DATA_CHANNEL_PORT 9099
#define RUNNING 1
#define RECIEVEING 1

int main() {
    //declaring important data
    int client_command_fd, client_data_fd;
    struct sockaddr_in server_command_addr;
    struct sockaddr_in server_data_addr;
    char buffer[BUFFER_SIZE];
    char recv_buf[BUFFER_SIZE] = {0};

    //Creating a server socket
    if(!(client_command_fd = socket(AF_INET, SOCK_STREAM, 0))) {
        printf("Failed to create socket!\nExiting..");
        exit(1);
    }

    if(!(client_data_fd = socket(AF_INET, SOCK_STREAM, 0))) {
        printf("Failed to create socket!\nExiting..");
        exit(1);
    }

    //Assigning attributes to server_address
    server_command_addr.sin_family = AF_INET;
    server_command_addr.sin_port = htons(COMMAND_CHANNEL_PORT);
    server_command_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    server_data_addr.sin_family = AF_INET;
    server_data_addr.sin_port = htons(DATA_CHANNEL_PORT);
    server_data_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((connect(client_command_fd, (struct sockaddr *)&server_command_addr, sizeof(server_command_addr))) < 0) {
		printf("Failed to connect to the server!\nExiting\n");
        exit(1);
    }

    if ((connect(client_data_fd, (struct sockaddr *)&server_data_addr, sizeof(server_data_addr))) < 0) {
		printf("Failed to connect to the server!\nExiting\n");
        exit(1);
    }

	while(RUNNING){
        bzero(buffer, BUFFER_SIZE);
        bzero(recv_buf, BUFFER_SIZE);
		fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        send(client_command_fd, buffer, BUFFER_SIZE, 0);
        recv(client_command_fd, recv_buf, sizeof(recv_buf), 0);

        std::cout << recv_buf;
    }

    close(client_command_fd);
    close(client_data_fd);
}