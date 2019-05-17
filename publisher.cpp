#include "publisher.h"
#include <iostream>

Publisher::Publisher(string username, string password, string email, int age, int id) {
    this->username = username;
    this->password = password;
    this-> email = email;
    this->age = age;
    this->id = id;
    this->publisher = true;
}

void Publisher::add_film(Film* film) {
    films.push_back(film);
}