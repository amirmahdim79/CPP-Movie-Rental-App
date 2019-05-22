#include "movie.h"

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