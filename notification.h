#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include <string>

class Notification {
private:
    std::string message;
public:
    Notification(std::string message);
    std::string show_message();
};

#endif