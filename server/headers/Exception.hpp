#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>
#include <string>

#define USER_ALREADY_LOGGED_IN 1
#define INVALID_USERNAME_OR_PASSWORD 2
#define BAD_SEQUENCE_OF_COMMANDS 3
#define FILE_UNAVAILABLE 4
#define NEED_ACCOUNT_FOR_LOGIN 5
#define SYNTAX_ERROR_IN_PARAMETERS_OR_ARGUMENTS 6
#define UNKNOWN_ERROR 7

class Exception {
    public:
        Exception(int _error_num);
        void print_error();
    
    private:
        int error_num;

};

#endif