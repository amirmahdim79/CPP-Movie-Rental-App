#include "movie.h"

Film::Film(int year, int length, int price, string name, string summary, string director, int id) {
    this->year = year;
    this->length = length;
    this->price = price;
    this->name = name;
    this->summary = summary;
    this->director = director;
    this->id = id;
}

int Film::get_id() {
    return id;
}