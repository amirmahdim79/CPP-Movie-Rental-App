#include "exceptions.h"
#include <iostream>

class Error;

void UnknownCommand::show_message() {
    std::cout << "Not Found" << std::endl;
}

void BadRequest::show_message() {
    std::cout << "Bad Request" << std::endl;
}