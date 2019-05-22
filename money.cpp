#include "money.h"

Money::Money(int amount, int publisher_id, std::string film_name) {
    this->amount = amount;
    this->publisher_id = publisher_id;
    this->film_name = film_name;
}