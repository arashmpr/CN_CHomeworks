#include "Exception.hpp"

Exception::Exception(int _error_num) {
    error_num = _error_num;
}

void Exception::print_error() {
    std::cout << error_num << std::endl;
}