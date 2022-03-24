#ifndef USER_HPP
#define USER_HPP

class User {
    public:
        User(char *_username, char *password, bool _is_admin);
        bool check_is_admin();

    private:
        char *username;
        char *password;
        bool is_admin;
};

#endif