#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "user.h"
#include "movie.h"
#include <string>
#include <vector>

class Publisher : public User{
private:
    
public:
    Publisher(string username, string password, string email, int age, int id);
    int get_films_size();
    void add_film(Film* film);
    void has_film(int id);
    void delete_film(int id);
    Film* get_film(int id);
    void show_followers();
    void show_all_films();
    vector<Film*> get_films();
};

#endif