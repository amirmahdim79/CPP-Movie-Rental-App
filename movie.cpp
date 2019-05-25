#include "movie.h"
#include "user.h"

Film::Film(int year, int length, int price, string name, string summary, string director, int id, int publisher_id) {
    this->year = year;
    this->length = length;
    this->price = price;
    this->name = name;
    this->summary = summary;
    this->director = director;
    this->id = id;
    this->publisher_id = publisher_id;
    this->rate = 0;
}

int Film::get_id() {
    return id;
}

int Film::get_publisher_id() {
    return publisher_id;
}

void Film::set_ratings(Rate* rate) {
    ratings.push_back(rate);
}

void Film::increase_comment_id() {
    this->comment_id++;
}

void Film::set_comment(Comment* comment) {
    comments.push_back(comment);
}

Comment* Film::get_comment(int comment_id) {
    for (int i = 0; i < comments.size(); i++) {
        if (comment_id == comments[i]->get_id()) {
            return comments[i];
        }
    }
}

void Film::delete_comment(int comment_id) {
    for (int i = 0; i < comments.size(); i++) {
        if (comment_id == comments[i]->get_id()) {
            comments.erase(comments.begin() + i);
            return;
        }
    }
}

vector<Comment*> Film::get_comments() {
    return comments;
}

double Film::get_rate() {
    double new_rate = 0;
    for (int i = 0; i < ratings.size(); i++) {
        new_rate = new_rate + ratings[i]->get_score();
    }
    new_rate = new_rate / ratings.size();
    this->rate = new_rate;
    return new_rate;
}

void Film::add_user(User* user) {
    users.push_back(user);
}

vector<User*> Film::get_users() {
    return users;
}
