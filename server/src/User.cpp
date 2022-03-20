#include "User.hpp"

User::User(string _username, string _password, bool _is_admin) {
    username = _username;
    password = _password;
    is_admin = _is_admin;
}

string User::get_username() {
    return username;
}

string User::get_password() {
    return password;
}

bool User::is_user_admin() {
    return is_admin;
}