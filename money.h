#ifndef MONEY_H_
#define MONEY_H_

#include "movie.h"
#include <string>

class Money {
public:
    Money(int amount, int publisher_id, int film_id);
    int amount;
    int publisher_id;
    int film_id;
    int active;
    int get_amount() {return amount;}
    int get_publisher_id() {return publisher_id;}
    int get_film_id() {return film_id;} 
};

#endif