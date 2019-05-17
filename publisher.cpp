#include "publisher.h"

Publisher::Publisher(string username, string password, string email, int age, int id) {
    this->username = username;
    this->password = password;
    this-> email = email;
    this->age = age;
    this->id = id;
    this->publisher = true;
}