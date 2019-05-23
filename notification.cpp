#include "notification.h"

#include <iostream>

Notification::Notification(std::string message) {
    this->message = message;
}

std::string Notification::show_message() {
    return message;
}