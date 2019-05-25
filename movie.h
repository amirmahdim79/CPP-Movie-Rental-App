#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
#include <vector>
#include "rate.h"
#include "comment.h"
using namespace std;

class User;

class Film {
private:
    int publisher_id;
    int id;
    int year;
    int length;
    int price;
    int comment_id = 1;
    string name;
    string summary;
    string director;
    double rate;
    vector<Comment*> comments;
    vector<Rate*> ratings;
    vector<User*> users;
public:
    Film(int year, int length, int price, string name, string summary, string director, int id, int publisher_id);
    int get_id();
    int get_publisher_id();
    int get_year() {return year;}
    int get_length() {return length;}
    int get_price() {return price;}
    double get_rate();
    int get_comment_id() {return comment_id;}
    int get_comments_number() {return comments.size();}
    string get_name() {return name;}
    string get_summary() {return summary;}
    string get_director() {return director;}
    void set_year(int year) {this->year = year;}
    void set_length(int length) {this->year = length;}
    void set_price(int price) {this->price = price;}
    void set_name(string name) {this->name = name;}
    void set_summary(string summary) {this->summary = summary;}
    void set_director(string director) {this->director = director;}
    void set_ratings(Rate* rate);
    void set_comment(Comment* comment);
    void increase_comment_id();
    Comment* get_comment(int comment_id);
    vector<Comment*> get_comments();
    void delete_comment(int comment_id);
    void add_user(User* user);
    vector<User*> get_users();
};

#endif