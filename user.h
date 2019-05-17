#ifndef USER_H_
#define USER_H_

#include <string>
#include "movie.h"

class User {
protected:
    int id;
    int age;
    string username;
    string email;
    string password;
    bool publisher;
public:
    int get_id();
    string get_password();
    string get_username();
    bool is_publisher();

    virtual void add_film(Film* film) {}
};

#endif