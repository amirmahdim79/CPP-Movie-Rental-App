#ifndef ADMIN_H_
#define ADMIN_H_

#include "user.h"
#include "program.h"

#include <string>

class Program;

class Admin : public User {
private:
    int id;
    std::string username;
public:
    Admin(int id);
};

#endif