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

void User::add_to_read_notifications() {
    for (int i = 0; i < notifications.size(); i++) {
        read_notifications.push_back(notifications[i]);
    }
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

vector<Film*> User::get_bought_films() {
    return bought_films;
}

void User::delete_notifications() {
    notifications.clear();
}

void User::show_notifications() {
    std::cout << "#. Notification Message" << std::endl;
    int last_element = notifications.size() - 1;
    int index = 1;
    for (int i = last_element; i >= 0; i--) {
        std::cout << index << ". " << notifications[i]->show_message() << std::endl;
        index++;
    }
}

void User::show_read_notifications(int limit) {
    std::cout << "#. Notification Message" << std::endl;
    int last_element = read_notifications.size() - 1;
    int index = 1;
    for (int i = last_element; i >= 0; i--) {
        if (index == limit + 1)
            break;
        std::cout << index << ". " << read_notifications[i]->show_message() << std::endl;
        index++;
    }
}