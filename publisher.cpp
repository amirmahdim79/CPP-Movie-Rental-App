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

void Publisher::delete_film(int id) {
    for (int i = 0; i < films.size(); i++) {
        if (id == films[i]->get_id())
            films.erase(films.begin() + i);
    }
}

void Publisher::show_followers() {
    int location_to_delete = 0;
    vector<User*> temp = followers;
    int smallest_user = 0;
    vector<User*> sorted_followers;
    while(1) {
        if (temp.size() == 0)
            break;
        for (int i = 1; i < temp.size(); i++) {
            if (i == temp.size() - 1)
                break;
            if (temp[smallest_user]->get_id() > temp[i]->get_id()) {
                location_to_delete = i;
                smallest_user = i;
            }
        }
        sorted_followers.push_back(temp[smallest_user]);
        temp.erase(temp.begin() + location_to_delete);
        location_to_delete = 0;
        smallest_user = 0;
    }
    std::cout << "List of Followers" << std::endl << std::endl;
    std::cout << "#. User Id | User Username | User Email" << std::endl;
    for (int i = 0; i < sorted_followers.size(); i++) {
        std::cout << i + 1 << ". " << sorted_followers[i]->get_id() << " | " << sorted_followers[i]->get_username() << " | " << sorted_followers[i]->get_email() << std::endl;
    }
}

void Publisher::show_all_films() {
    std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
    for (int i = 0; i < films.size(); i++) {
        std::cout << i + 1 << ". " << films[i]->get_id() << " | " << films[i]->get_name() << " | " << films[i]->get_length() << " | " << films[i]->get_price() << " | " << films[i]->get_rate() << " | " << films[i]->get_year() << " | " << films[i]->get_director() << std::endl;
    }
}

vector<Film*> Publisher::get_films() {
    return films;
}

int Publisher::get_films_size() {
    return films.size();
}

void Publisher::send_notification_to_followers(Notification* notif) {
    for (int i = 0; i < followers.size(); i++) {
        followers[i]->add_to_notifications(notif);
    }
}