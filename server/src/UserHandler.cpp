#include "UserHandler.hpp"

std::vector<User*> UserHandler::users;

User* UserHandler::find_user(std::string username) {
    for(User* user : UserHandler::users)
    {
        if(user->get_username() == username)
            return user;
    }
    throw INVALID_USERNAME_OR_PASSWORD;
}