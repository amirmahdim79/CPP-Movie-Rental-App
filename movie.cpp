#include "movie.h"

Movie::Movie(int year, int length, int price, string name, string summary, string director) {
    this->year = year;
    this->length = length;
    this->price = price;
    this->name = name;
    this->summary = summary;
    this->director = director;
}