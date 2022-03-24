#include "ConfigParser.hpp"

ConfigParser::ConfigParser(std::string _config_file_path) {
    config_file_path = _config_file_path;
    parse();
}

void ConfigParser::parse() {
    std::ifstream config_file(config_file_path);
    json json_file;
    config_file >> json_file;
    for (auto& user: json_file["users"]) {
        users.push_back(
            new User(
            user["user"].get<std::string>(),
            user["password"].get<std::string>(),
            user["admin"].get<std::string>() == "true")
        );
    }
    for (auto& protected_file: json_file["files"])
        protected_files.push_back(protected_file.get<std::string>());
}

std::vector<User*> ConfigParser::get_users() {
    return users;
}

std::vector<std::string> ConfigParser::get_protected_files() {
    return protected_files;
}

void ConfigParser::print_user() {
    for (auto& user: users) {
        if(user -> check_is_admin()) {
            std::cout<< "sag" << std::endl;
        } else {
            std::cout<< "sag nist" << std::endl;
        }
    }
}