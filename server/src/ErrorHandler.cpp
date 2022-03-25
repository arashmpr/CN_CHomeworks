#include "ErrorHandler.hpp"

BadSequenceOfCommands::BadSequenceOfCommands() {
	message = ERROR_BAD_SEQUENCE_OF_COMMANDS_TEXT;
}

BadSequenceOfCommands::~BadSequenceOfCommands() {}

const char *BadSequenceOfCommands::what() const throw() {
	return message.c_str();
}


InvalidUsernameOrPassword::InvalidUsernameOrPassword() {
	message = ERROR_INAVLID_USERNAME_OR_PASSWORD_TEXT;
}

InvalidUsernameOrPassword::~InvalidUsernameOrPassword() {}

const char *InvalidUsernameOrPassword::what() const throw() {
	return message.c_str();
}

FileUnavailable::FileUnavailable() {
	message = ERROR_FILE_UNAVAILABLE_TEXT;
}

FileUnavailable::~FileUnavailable() {}

const char *FileUnavailable::what() const throw() {
	return message.c_str();
}


NeedAccountForLogin::NeedAccountForLogin() {
	message = ERROR_NEED_ACCOUNT_FOR_LOGIN_TEXT;
}

NeedAccountForLogin::~NeedAccountForLogin() {}

const char *NeedAccountForLogin::what() const throw() {
	return message.c_str();
}


SyntaxErrorInParametersOrArguments::SyntaxErrorInParametersOrArguments() {
	message = ERROR_SYNTAX_ERROR_IN_PARAMETERS_OR_ARGUMENTS_TEXT;
}

SyntaxErrorInParametersOrArguments::~SyntaxErrorInParametersOrArguments() {}

const char *SyntaxErrorInParametersOrArguments::what() const throw() {
	return message.c_str();
}


Error::Error() {
	message = ERROR_ERROR_TEXT;
}

Error::~Error() {}

const char *Error::what() const throw() {
	return message.c_str();
}


CantOpenDataConnection::CantOpenDataConnection() {
	message = ERROR_CANT_OPEN_DATA_CONNECTION_TEXT;
}

CantOpenDataConnection::~CantOpenDataConnection() {}

const char *CantOpenDataConnection::what() const throw() {
	return message.c_str();
}