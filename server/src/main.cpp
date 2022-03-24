#include "Server.hpp"
#include "ConfigParser.hpp"
#include "User.hpp"

int main() {
    ConfigParser *parsed_config = new ConfigParser("config.json");
    std::vector<User*> users = parsed_config -> get_users();
    std::vector<std::string> protected_files = parsed_config -> get_protected_files();

    Server *server = new Server(users, protected_files);
    server -> run();
}