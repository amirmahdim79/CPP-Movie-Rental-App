#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "user.h"
#include "movie.h"
#include <string>
#include <vector>

class Publisher : public User{
private:
    vector<Film*> films;
public:
    Publisher(string username, string password, string email, int age, int id);
    void add_film(Film* film);
};

#endif