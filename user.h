#ifndef USER_H_
#define USER_H_

#include <string>
#include <vector>
#include "movie.h"
#include "notification.h"

class User {
protected:
    int id;
    int age;
    int money;
    string username;
    string email;
    string password;
    bool publisher;
    vector<Film*> films;
    vector<Film*> bought_films;
    vector<User*> followers;
    vector<User*> following;
    vector<Notification*> notifications;
    vector<Notification*> read_notifications;
public:
    int get_id();
    int get_money();
    string get_password();
    string get_username();
    string get_email();
    virtual void follow(User* user);
    virtual void buy_film(Film* film);

    virtual int get_films_size() {return films.size();}
    virtual Film* get_film(int id) {}
    virtual vector<Film*> get_films() {}
    virtual vector<Film*> get_bought_films();

    bool is_publisher();

    virtual void add_film(Film* film) {}
    virtual void has_film(int id) {}
    virtual void delete_film(int id) {}
    virtual void show_followers() {}
    virtual void show_all_films() {}
    virtual void show_notifications();
    virtual void add_to_notifications(Notification* notif);
    virtual void add_to_read_notifications();
    virtual void show_read_notifications(int limit);
    virtual void delete_notifications();
    virtual void add_to_followers(User* user);
    virtual void send_notification_to_followers(Notification* notif) {}
    virtual void increase_money(int amount);
    virtual void decrese_money(int amount);
    //virtual void
};

#endif