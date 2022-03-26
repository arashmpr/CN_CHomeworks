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
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char recv_buf[BUFFER_SIZE] = {0};

    //Creating a server socket
    if(!(client_fd = socket(AF_INET, SOCK_STREAM, 0))) {
        printf("Failed to create socket!\nExiting..");
        exit(1);
    }

    //Assigning attributes to server_address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(COMMAND_CHANNEL_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
		printf("Failed to connect to the server!\nExiting\n");
        exit(1);
    }
    

	while(RUNNING){
        bzero(buffer, BUFFER_SIZE);
        bzero(recv_buf, BUFFER_SIZE);
		fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        send(client_fd, buffer, BUFFER_SIZE, 0);
        recv(client_fd, recv_buf, sizeof(recv_buf), 0);

        std::cout << recv_buf;
    }

    close(client_fd);
}