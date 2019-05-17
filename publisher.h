#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "user.h"

class Publisher : public User{
private:
public:
    Publisher(string username, string password, string email, int age, int id);
};

#endif