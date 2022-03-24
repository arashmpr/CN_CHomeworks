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

#define BUFFER_SIZE 1024

class CommandHandler {
    public:
        CommandHandler(int _client_fd, char *_cmd_line);
        void run_command();
    private:
        int client_fd;
        // User *user;

        char *cmd_line;
        char *cmd;

        void pwd_handler();
        void mkd_handler(char *file_path);
        void delete_file_handler(char *file_path);
        void delete_dir_handler(char *file_path);
        void ls_handler();
        void cwd_handler(char *path_file);
        void rename_file_handler(const char *old_name, const char *new_name);
};

#endif