#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

#include <iostream>
#include <string>
#include <exception>

#define ERROR_BAD_SEQUENCE_OF_COMMANDS_TEXT "503: Bad sequence of commands.\n"
#define ERROR_INAVLID_USERNAME_OR_PASSWORD_TEXT "430: Invalid username or password\n"
#define ERROR_FILE_UNAVAILABLE_TEXT "550: File unavailable.\n"
#define ERROR_NEED_ACCOUNT_FOR_LOGIN_TEXT "332: Need account for login.\n"
#define ERROR_SYNTAX_ERROR_IN_PARAMETERS_OR_ARGUMENTS_TEXT "501: Syntax error in parameters or arguments.\n"
#define ERROR_ERROR_TEXT "500: Error\n"
#define ERROR_CANT_OPEN_DATA_CONNECTION_TEXT "425: Can’t open data connection.\n"

class BadSequenceOfCommands : public std::exception {
    private:
        std::string message;
    public:
        BadSequenceOfCommands();
        ~BadSequenceOfCommands();

        const char *what() const throw();
};

class InvalidUsernameOrPassword : public std::exception {
    private:
        std::string message;
    public:
        InvalidUsernameOrPassword();
        ~InvalidUsernameOrPassword();

        const char *what() const throw();
};

class FileUnavailable : public std::exception {
    private:
        std::string message;
    public:
        FileUnavailable();
        ~FileUnavailable();

        const char *what() const throw();
};

class NeedAccountForLogin : public std::exception {
    private:
        std::string message;
    public:
        NeedAccountForLogin();
        ~NeedAccountForLogin();

        const char *what() const throw();
};

class SyntaxErrorInParametersOrArguments : public std::exception {
    private:
        std::string message;
    public:
        SyntaxErrorInParametersOrArguments();
        ~SyntaxErrorInParametersOrArguments();

        const char *what() const throw();
};

class Error : public std::exception {
    private:
        std::string message;
    public:
        Error();
        ~Error();

        const char *what() const throw();
};

class CantOpenDataConnection : public std::exception {
    private:
        std::string message;
    public:
        CantOpenDataConnection();
        ~CantOpenDataConnection();

        const char *what() const throw();
};

#endif