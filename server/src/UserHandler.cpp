#include "UserHandler.hpp"

std::vector<User*> UserHandler::users;

User* UserHandler::find_user(char* username) {
    for(User* user : UserHandler::users)
    {
        if(user->get_username() == username)
            return user;
    }
    throw InvalidUsernameOrPassword();
}