#include "Logger.hpp"

Logger::Logger() {
    log_file.open("log.txt", std::ios::out | std::ios::app);
}

Logger::~Logger() {
    log_file.close();
}

void Logger::current_time() {
    auto temp_time = std::chrono::system_clock::now();
    time = std::chrono::system_clock::to_time_t(temp_time);
}

void Logger::add_log(std::string massage) {
    current_time();
    log_file << massage << " At: " << std::ctime(&time) << std::endl;
}