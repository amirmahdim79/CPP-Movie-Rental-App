#ifndef MONEY_H_
#define MONEY_H_

#include "movie.h"
#include <string>

class Money {
public:
    Money(int amount, int publisher_id, std::string film_name);
    int amount;
    int publisher_id;
    std::string film_name;
};

#endif