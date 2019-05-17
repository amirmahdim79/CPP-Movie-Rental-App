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
};

#endif