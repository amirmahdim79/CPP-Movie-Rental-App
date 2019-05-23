#include "money.h"

Money::Money(int amount, int publisher_id, int film_id) {
    this->amount = amount;
    this->publisher_id = publisher_id;
    this->film_id = film_id;
    this->active = 1;
}