#include "user.h"
#include <iostream>

string User::get_password() {
    return password;
}

string User::get_username() {
    return username;
}

string User::get_email() {
    return email;
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

void User::increase_money(int amount) {
    money = money + amount;
}

void User::decrese_money(int amount) {
    this->money = this->money - amount;
}

void User::buy_film(Film* film) {
    bought_films.push_back(film);
}