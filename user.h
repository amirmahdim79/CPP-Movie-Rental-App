#ifndef USER_H_
#define USER_H_

#include <string>
#include <vector>
#include "movie.h"

class User {
protected:
    int id;
    int age;
    string username;
    string email;
    string password;
    bool publisher;
    vector<Film*> films;
public:
    int get_id();
    string get_password();
    string get_username();
    bool is_publisher();

    virtual void add_film(Film* film) {}
    virtual void has_film(int id) {}
    virtual Film* get_film(int id) {}
};

#endif