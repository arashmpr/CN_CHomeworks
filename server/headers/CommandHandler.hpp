#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

class CommandHandler {
    public:
        CommandHandler(char *_cmd_line);
        void run_command();
    private:
        char *cmd_line;
        char *cmd;
};

#endif