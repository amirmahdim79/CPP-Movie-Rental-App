#include "user.h"

string User::get_password() {
    return password;
}

string User::get_username() {
    return username;
}

int User::get_id() {
    return id;
}

bool User::is_publisher() {
    if (publisher == true)
        return true;
    else
        return false;
}

void User::follow(User* user) {
    following.push_back(user);
}

void User::add_to_notifications(Notification* notif) {
    notifications.push_back(notif);
}