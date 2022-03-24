#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#include <CommandHandler.hpp>
#include <User.hpp>

#define BUFFER_SIZE 1024
#define COMMAND_CHANNEL_PORT 9009
#define DATA_CHANNEL_PORT 9099
#define RUNNING 1
#define RECIEVEING 1

class Server {
    public:
        Server(std::vector <std::string> _protected_files);
        void run();
    
    private:
        int command_fd, data_fd;

        std::vector <std::string> protected_files;


        int run_socket(int port);

};

#endif