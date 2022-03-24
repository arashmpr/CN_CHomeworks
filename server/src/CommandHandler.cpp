#include "CommandHandler.hpp"

CommandHandler::CommandHandler(int _client_fd, char *_cmd_line) {
    client_fd = _client_fd;
    cmd_line = _cmd_line;
}

void CommandHandler::run_command() {
    try {
            cmd = strtok(cmd_line, " ");

        if (strcmp(cmd_line, "user") == 0) {
            log_in_handler();
        } 

        if (strcmp(cmd_line, "pass") == 0) {
            password_handler();
        } 
    
        if (strcmp(cmd_line, "pwd") == 0) {
            pwd_handler();
            exit(1);
        } 
        else if (strcmp(cmd_line, "mkd") == 0) {
            char *file_path =  strtok(NULL," ");
            mkd_handler(file_path);
        }   
        else if (strcmp(cmd_line, "dele") == 0) {
            char *mode = strtok(NULL, " ");
            char *path_file = strtok(NULL, " ");
            if (strcmp(mode, "-f") == 0) {
                delete_file_handler(path_file);
            } else if (strcmp(mode, "-d") == 0) {
                delete_dir_handler(path_file);
            }
        } else if (strcmp(cmd_line, "ls") == 0) {
            ls_handler();
        } else if (strcmp(cmd_line, "cwd") == 0) {
            char *path_file = strtok(NULL, " ");
            cwd_handler(path_file);
        } else if (strcmp(cmd_line, "rename") == 0) {
            char *old_name = strtok(NULL, " ");
            char *new_name = strtok(NULL, " ");
            rename_file_handler(old_name, new_name);
        }
    } catch(int error_num) {
        Exception *error = new Exception(error_num);
        error -> print_error();
    }

}

void CommandHandler::log_in_handler() {
    char *username = strtok(NULL, " ");
    if (is_user_logged_in) {
        std::cout << "User already logged in!" << std::endl;
    } else {
        found_user = UserHandler::find_user(username);
        if(found_user) {
            std::cout << "User name okay, need password." << std::endl;
            is_user_ready_to_enter_password = true;
        } else {
            std::cout << "User not found!" << std::endl;
        }
            
    }
}

void CommandHandler::password_handler() {
    char *password = strtok(NULL, " ");

    std::string found_user_password = found_user -> get_password();
    std::cout << found_user_password << std::endl;

    if (password == found_user_password) {
        std::cout << "User logged in, proceed. Log out if appropriate." << std::endl;
        is_user_logged_in = true;
        is_user_ready_to_enter_password = false;
    } else {
        std::cout << "Pass is incorrect." << std::endl;
    }
}

void CommandHandler::pwd_handler() {
    if(!is_user_logged_in) {
        throw INVALID_USERNAME_OR_PASSWORD;
    }

    char directory[BUFFER_SIZE];
    if(getcwd(directory, sizeof(directory)) != NULL) {
        printf("%s\n", directory);
    } else {
        printf("Error in working directory!\n");
    }
}

void CommandHandler::mkd_handler(char *path_file) {
    if(!is_user_logged_in) {
        throw INVALID_USERNAME_OR_PASSWORD;
    }

    int status = mkdir(path_file, 0777);
    if (status == -1) {
        perror("mkdir");
        exit(1);
    }
    printf("%s created.\n", path_file);
}

void CommandHandler::delete_file_handler(char *path_file) {
    if(!is_user_logged_in) {
        throw INVALID_USERNAME_OR_PASSWORD;
    }

    int status = unlink(path_file);
    if (status == -1) {
        perror("unlink");
        exit(1);
    }
    printf("%s deleted.\n", path_file);

}

void CommandHandler::delete_dir_handler(char *path_file) {
    if(!is_user_logged_in) {
        throw INVALID_USERNAME_OR_PASSWORD;
    }

    int status = rmdir(path_file);
    if (status == -1) {
        perror("rmdir");
        exit(1);
    }
    printf("%s deleted.\n", path_file);
}

void CommandHandler::ls_handler() {
    if(!is_user_logged_in) {
        throw INVALID_USERNAME_OR_PASSWORD;
    }

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

void CommandHandler::cwd_handler(char *path_file) {
    if(!is_user_logged_in) {
        throw INVALID_USERNAME_OR_PASSWORD;
    }

    int status = chdir(path_file);
    if (status == -1) {
        perror("chdir");
        exit(1);
    }
    printf("Successful change.\n");
}

void CommandHandler::rename_file_handler(const char *old_name, const char *new_name) {
    if(!is_user_logged_in) {
        throw INVALID_USERNAME_OR_PASSWORD;
    }

    int status = rename(old_name, new_name);
    if (status == -1) {
        perror("rename");
        exit(1);
    }
    printf("Successful change.\n");
}