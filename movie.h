#ifndef MOVIE_H_
#define MOVIE_H_

#include <string>
using namespace std;

class Movie {
private:
    int year;
    int length;
    int price;
    string name;
    string summary;
    string director;
public:
    Movie(int year, int length, int price, string name, string summary, string director);
};

#endif