#ifndef USER
#define USER

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class User {
    public: 
        User(
            string username,
            string password,

            bool is_admin
        );

        string get_username();
        string get_password();
        bool is_user_admin();

    private:
        string username;
        string password;
        bool is_admin;



    
}

#endif