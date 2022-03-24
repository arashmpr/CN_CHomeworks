#include "Server.hpp"
#include "ConfigParser.hpp"
#include "User.hpp"
#include "UserHandler.hpp"

int main() {
    ConfigParser *parsed_config = new ConfigParser("config.json");
    UserHandler::users = parsed_config -> get_users();
    std::vector<std::string> protected_files = parsed_config -> get_protected_files();

    Server *server = new Server(protected_files);
    server -> run();
}