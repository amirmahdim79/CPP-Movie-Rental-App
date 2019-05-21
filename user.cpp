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

int User::get_money() {
    return money;
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

void User::add_to_followers(User* user) {
    followers.push_back(user);
}

void User::add_to_notifications(Notification* notif) {
    notifications.push_back(notif);
}

void User::send_notification_to_followers(Notification* notif) {
    for (int i = 0; i < followers.size(); i++) {
        followers[i]->add_to_notifications(notif);
    }
}

void User::increase_money(int amount) {
    money = money + amount;
}