#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
using namespace std;

class Film {
private:
    int id;
    int year;
    int length;
    int price;
    string name;
    string summary;
    string director;
public:
    Film(int year, int length, int price, string name, string summary, string director, int id);
    int get_id();
    int get_year() {return year;}
    int get_length() {return length;}
    int get_price() {return price;}
    string get_name() {return name;}
    string get_summary() {return summary;}
    string get_director() {return director;}
    void set_year(int year) {this->year = year;}
    void set_length(int length) {this->year = length;}
    void set_price(int price) {this->price = price;}
    void set_name(string name) {this->name = name;}
    void set_summary(string summary) {this->summary = summary;}
    void set_director(string director) {this->director = director;}
};

#endif