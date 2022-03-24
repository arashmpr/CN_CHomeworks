#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>

class User {
    public:
        User(std::string _username, std::string _password, bool _is_admin);
        bool check_is_admin();

    private:
        std::string username;
        std::string password;
        bool is_admin;
};

#endif