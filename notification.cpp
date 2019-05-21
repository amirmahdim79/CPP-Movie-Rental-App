#include "notification.h"

#include <iostream>

Notification::Notification(std::string message) {
    this->message = message;
}

void Notification::show_message() {
    std::cout << message << std::endl;
}