#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>

class Logger {
    
    private:
        std::fstream log_file;
        std::time_t time;

    public:
        Logger();
        ~Logger();
        void current_time();
        void add_log(std::string massage);
};

#endif