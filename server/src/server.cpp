#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define PORT 8080
#define RUNNING 1
#define RECIEVEING 1

void pwd();
void mkd(char *file_path);
void delete_file(char *file_path);
void delete_dir(char *file_path);
void ls();
void cwd(char *path_file);
void rename_file(const char *old_name, const char *new_name);

int main() {
    //declaring important data
    char *ip = "127.0.0.1";
    int serverfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    //Creating a server socket
    if(!(serverfd = socket(AF_INET, SOCK_STREAM, 0))) {
        printf("Failed to create socket!\nExiting..");
        exit(1);
    }

    //Assigning attributes to server_address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    //Binding the socket 
    if ((bind(serverfd, (struct sockaddr*) &server_addr, sizeof(server_addr))) < 0) {
        printf("Failed to bind the connection!\nExiting..\n");
        exit(1);
    }

    //Listening on the server
    if((listen(serverfd, 10)) < 0) {
        printf("Failed to listen!\nExiting..\n");
        exit(1);
    }

    while(RUNNING) {
        int clientfd;
        int addr_len = sizeof(server_addr);
        printf("Wainting for connection...\n");
        
        //accepting a new connection
        if(!(clientfd = accept(serverfd, (struct sockaddr*) &server_addr, (socklen_t*) &addr_len))) {
            printf("Couldn't accept the client!\n");
            continue;
        }

        printf("Successfully connected to a client!\n");  

        while(RECIEVEING) {
            recv(clientfd, buffer, BUFFER_SIZE, 0);

            char *cmd = strtok(buffer, " ");

            if (strcmp(buffer, "pwd") == 0) {
                pwd();
                exit(1);
            } 
            else if (strcmp(buffer, "mkd") == 0) {
                char *file_path =  strtok(NULL," ");
                mkd(file_path);
            }
            else if (strcmp(buffer, "dele") == 0) {
                char *mode = strtok(NULL, " ");
                char *path_file = strtok(NULL, " ");
                if (strcmp(mode, "-f") == 0) {
                    delete_file(path_file);
                } else if (strcmp(mode, "-d") == 0) {
                    delete_dir(path_file);
                }
            } else if (strcmp(buffer, "ls") == 0) {
                ls();
            } else if (strcmp(buffer, "cwd") == 0) {
                char *path_file = strtok(NULL, " ");
                cwd(path_file);
            } else if (strcmp(buffer, "rename") == 0) {
                char *old_name = strtok(NULL, " ");
                char *new_name = strtok(NULL, " ");
                rename_file(old_name, new_name);
            }
        }

        close(clientfd);
    }
    close(serverfd);
    return 0;
}

void pwd() {
    char pwd[BUFFER_SIZE];

    if(getcwd(pwd, sizeof(pwd)) != NULL) {
        printf("%s\n", pwd);
    } else {
        printf("Error in working directory!\n");
    }
}

void mkd(char *path_file) {
       int status = mkdir(path_file, 0777);
       if (status == -1) {
           perror("mkdir");
           exit(1);
       }
       printf("%s created.\n", path_file);
}

void delete_file(char *path_file) {
    int status = unlink(path_file);
    if (status == -1) {
        perror("unlink");
        exit(1);
    }
    printf("%s deleted.\n", path_file);

}

void delete_dir(char *path_file) {
    int status = rmdir(path_file);
    if (status == -1) {
        perror("rmdir");
        exit(1);
    }
    printf("%s deleted.\n", path_file);
}

void ls() {
    DIR *parent_dir;
    struct dirent *current_dir;
    parent_dir = opendir(".");
    struct stat file_status;
    if (parent_dir) {
        while ((current_dir = readdir(parent_dir)) != NULL){
            if (stat(current_dir->d_name, &file_status) < 0){
                printf("handleLS: stat problem\n");
                exit(1);
            }
            else{
                printf("%s\n", current_dir->d_name);
            }
        }
    }
}

void cwd(char *path_file) {
    int status = chdir(path_file);
    if (status == -1) {
        perror("chdir");
        exit(1);
    }
    printf("Successful change.\n");
}

void rename_file(const char *old_name, const char *new_name) {
    int status = rename(old_name, new_name);
    if (status == -1) {
        perror("rename");
        exit(1);
    }
    printf("Successful change.\n");
}