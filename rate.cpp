#include "rate.h"

Rate::Rate(int score, int user_id, int film_id) {
    this->score = score;
    this->user_id = user_id;
    this->film_id = film_id;
}

int Rate::get_score() {
    return score;
}