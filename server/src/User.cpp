#include "User.hpp"

User::User(std::string _username, std::string _password, bool _is_admin) {
    username = _username;
    password = _password;
    is_admin = _is_admin;
}

std::string User::get_username() {
    return username;
}

std::string User::get_password() {
    return password;
}

bool User::check_is_admin() {
    return is_admin;
}
