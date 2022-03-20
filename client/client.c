#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define PORT 8080
#define RUNNING 1
#define RECIEVEING 1

void pwd(int clientfd);

int main() {
    //declaring important data
    char *ip = "127.0.0.1";
    int clientfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    //Creating a server socket
    if(!(clientfd = socket(AF_INET, SOCK_STREAM, 0))) {
        printf("Failed to create socket!\nExiting..");
        exit(1);
    }

    //Assigning attributes to server_address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if ((connect(clientfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
		printf("Failed to connect to the server!\nExiting\n");
        exit(1);
    }

	while(RUNNING){
        bzero(buffer, BUFFER_SIZE);
		fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        char cmd_line[BUFFER_SIZE];
		strcpy(cmd_line,buffer);
		char* cmd = strtok(cmd_line," ");

        if (strcmp(cmd, "pwd") == 0) {
            send(clientfd, buffer, BUFFER_SIZE, 0);
            exit(1);
        } else {
            send(clientfd, buffer, BUFFER_SIZE, 0);
        }
    }


}