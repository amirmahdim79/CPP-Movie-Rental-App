#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "user.h"

class Customer : public User {
private:
public:
    Customer(string username, string password, string email, int age, int id);
};

#endif