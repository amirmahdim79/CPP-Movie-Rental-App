#ifndef RATE_H_
#define RATE_H_

class Rate {
private:
    int score;
    int user_id;
    int film_id;
public:
    Rate(int score, int user_id, int film_id);
    int get_score();

};

#endif