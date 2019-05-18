#include "publisher.h"
#include "exceptions.h"
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

void Publisher::has_film(int id) {
    for (int i = 0; i < films.size(); i++) {
        if (films[i]->get_id() == id) {
            return;
        }
    }
    Error* e = new PermissionDenied;
    throw e;
}

Film* Publisher::get_film(int id) {
    for (int i = 0; i < films.size(); i++) {
        if (id == films[i]->get_id())
            return films[i];
    }
}