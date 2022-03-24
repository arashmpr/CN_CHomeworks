#include "CommandHandler.hpp"

void pwd_handler();
void mkd(char *file_path);
void delete_file(char *file_path);
void delete_dir(char *file_path);
void ls();
void cwd(char *path_file);
void rename_file(const char *old_name, const char *new_name);

CommandHandler::CommandHandler(char *_cmd_line) {
    cmd_line = _cmd_line;
}

void CommandHandler::run_command() {
    cmd = strtok(cmd_line, " ");
    
    if (strcmp(cmd_line, "pwd") == 0) {
        pwd_handler();
        exit(1);
    } 
    else if (strcmp(cmd_line, "mkd") == 0) {
        char *file_path =  strtok(NULL," ");
        mkd(file_path);
    }
    else if (strcmp(cmd_line, "dele") == 0) {
        char *mode = strtok(NULL, " ");
        char *path_file = strtok(NULL, " ");
        if (strcmp(mode, "-f") == 0) {
            delete_file(path_file);
        } else if (strcmp(mode, "-d") == 0) {
            delete_dir(path_file);
        }
    } else if (strcmp(cmd_line, "ls") == 0) {
        ls();
    } else if (strcmp(cmd_line, "cwd") == 0) {
        char *path_file = strtok(NULL, " ");
        cwd(path_file);
    } else if (strcmp(cmd_line, "rename") == 0) {
        char *old_name = strtok(NULL, " ");
        char *new_name = strtok(NULL, " ");
        rename_file(old_name, new_name);
    }
}

void pwd_handler() {
    char directory[BUFFER_SIZE];

    if(getcwd(directory, sizeof(directory)) != NULL) {
        printf("%s\n", directory);
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