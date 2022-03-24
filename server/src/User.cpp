#include "User.hpp"

User::User(char *_username, char *_password, bool _is_admin) {
    username = _username;
    password = _password;
    is_admin = _is_admin;
}

bool User::check_is_admin() {
    return is_admin;
}
