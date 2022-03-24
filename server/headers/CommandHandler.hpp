#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "User.hpp"
#include "UserHandler.hpp"
#include "Exception.hpp"

#define BUFFER_SIZE 1024

class CommandHandler {
    public:
        CommandHandler(int _client_fd, char* _cmd_line);
        void run_command();
    private:
        int client_fd;

        char* cmd_line;
        char* cmd;

        User* found_user;

        bool is_user_logged_in;
        bool is_user_ready_to_enter_password;

        void log_in_handler();
        void password_handler();
        void pwd_handler();
        void mkd_handler(char* file_path);
        void delete_file_handler(char* file_path);
        void delete_dir_handler(char* file_path);
        void ls_handler();
        void cwd_handler(char* path_file);
        void rename_file_handler(const char* old_name, const char* new_name);
};

#endif