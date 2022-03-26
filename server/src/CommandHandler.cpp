#include "CommandHandler.hpp"

CommandHandler::CommandHandler(int _client_fd, char* _cmd_line) {
    client_fd = _client_fd;
    cmd_line = _cmd_line;
    logger = new Logger();
}

void CommandHandler::run_command() {
    try {
        cmd = strtok(cmd_line, " ");

        if (strcmp(cmd_line, "user") == 0) {
            log_in_handler();
        } 
        else if (strcmp(cmd_line, "pass") == 0) {
            password_handler();
        } 
        else if (strcmp(cmd_line, "pwd") == 0) {
            pwd_handler();
        } 
        else if (strcmp(cmd_line, "mkd") == 0) {
            char* file_path =  strtok(NULL," ");
            mkd_handler(file_path);
        }   
        else if (strcmp(cmd_line, "dele") == 0) {
            char* mode = strtok(NULL, " ");
            char* path_file = strtok(NULL, " ");
            if (strcmp(mode, "-f") == 0) {
                delete_file_handler(path_file);
            } 
            else if (strcmp(mode, "-d") == 0) {
                delete_dir_handler(path_file);
            }
        } 
        else if (strcmp(cmd_line, "ls") == 0) {
            ls_handler();
        } 
        else if (strcmp(cmd_line, "cwd") == 0) {
            char* path_file = strtok(NULL, " ");
            cwd_handler(path_file);
        } 
        else if (strcmp(cmd_line, "rename") == 0) {
            char* old_name = strtok(NULL, " ");
            char* new_name = strtok(NULL, " ");
            rename_file_handler(old_name, new_name);
        }
        else if (strcmp(cmd_line, "quit") == 0) {
            quit_handler();
        } 
        else {
            throw SyntaxErrorInParametersOrArguments();
        }
    } catch(std::exception &er) {
        std::string error = er.what();
        send(client_fd, error.data(), error.size(), 0);
    }
}

void CommandHandler::log_in_handler() {
    char* username = strtok(NULL, " ");
    found_user = UserHandler::find_user(username);
    if(found_user) {
        is_user_ready_to_enter_password = true;
        std::string response = RESPONSE_USERNAME_OKAY_NEED_PASSWORD_TEXT;
        send(client_fd, response.data(), response.size(), 0);
    } else {
        throw InvalidUsernameOrPassword();
    }
}

void CommandHandler::password_handler() {
    if (!is_user_ready_to_enter_password) {
        throw BadSequenceOfCommands();
    }

    char* password = strtok(NULL, " ");

    std::string found_user_password = found_user -> get_password();

    if (password == found_user_password) {
        is_user_logged_in = true;
        is_user_ready_to_enter_password = false;
        
        logger -> add_log("User '" + found_user -> get_username() + "' logged in successfully.");
        std::string response = RESPONSE_USER_LOGGED_IN_PROCEED_TEXT;
        send(client_fd, response.data(), response.size(), 0);
    } else {
        throw InvalidUsernameOrPassword();
    }
}

void CommandHandler::pwd_handler() {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
    }

    std::string current_directory = getenv("PWD");

    std::string response = "257: " + current_directory + "\n";
    send(client_fd, response.data(), response.size(), 0);
}

void CommandHandler::mkd_handler(char* path_file) {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
    }

    int status = mkdir(path_file, 0777);
    if (status == -1) {
        throw Error();
    }
    logger -> add_log("User '" + found_user -> get_username() + "' created a file in '" + std::string(path_file) +"' successfully.");

    std::string response = "257: " + std::string(path_file) + " created.\n";
    send(client_fd, response.data(), response.size(), 0);
}

void CommandHandler::delete_file_handler(char* path_file) {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
    }

    int status = unlink(path_file);
    if (status == -1) {
        throw Error();
    }
    logger -> add_log("User '" + found_user -> get_username() + "' deleted the file '" + std::string(path_file) +"' successfully.");

    std::string response = "250: " + std::string(path_file) + " deleted.\n";
    send(client_fd, response.data(), response.size(), 0);
}

void CommandHandler::delete_dir_handler(char* path_file) {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
    }

    int status = rmdir(path_file);
    if (status == -1) {
        throw Error();
    }
    logger -> add_log("User '" + found_user -> get_username() + "' deleted the directory '" + std::string(path_file) +"' successfully.");

    std::string response = "250: " + std::string(path_file) + " deleted.\n";
    send(client_fd, response.data(), response.size(), 0);
}

void CommandHandler::ls_handler() {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
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

void CommandHandler::cwd_handler(char* path_file) {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
    }

    int status = chdir(path_file);
    if (status == -1) {
        throw Error();
    }
    logger -> add_log("User '" + found_user -> get_username() + "' changed the working directory to '" + std::string(path_file) +"' successfully.");

    std::string response = "250: Successful change.\n";
    send(client_fd, response.data(), response.size(), 0);
}

void CommandHandler::rename_file_handler(const char* old_name, const char* new_name) {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
    }

    int status = rename(old_name, new_name);
    if (status == -1) {
        perror("rename");
        exit(1);
    }
    printf("Successful change.\n");
    logger -> add_log("User '" + found_user -> get_username() + "' rename file from '" + std::string(old_name) +"' to '" + std::string(new_name) + "'successfully.");

    std::string response = "250: Successful change.\n";
    send(client_fd, response.data(), response.size(), 0);
}

void CommandHandler::quit_handler() {
    if(!is_user_logged_in) {
        throw NeedAccountForLogin();
    }
    logger -> add_log("User '" + found_user -> get_username() + "' logged out.");
    is_user_logged_in = false;

    std::string response = "221: Successful Quit.\n";
    send(client_fd, response.data(), response.size(), 0);

    close(client_fd);
    exit(1);
}