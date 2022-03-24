#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

#include "User.hpp"
#include "Json.hpp"

using json = nlohmann::json;

class ConfigParser {
    public:
        ConfigParser(std::string _config_file_path);
        std::vector<User*> get_users();
        std::vector<std::string> get_protected_files();
        void print_user();
    private:
        std::string config_file_path;
        std::vector<User*> users;
        std::vector<std::string> protected_files;

        void parse();
};

#endif