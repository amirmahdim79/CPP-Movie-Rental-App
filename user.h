#ifndef USER_H_
#define USER_H_

#include <string>
using namespace std;

class User {
protected:
    int id;
    int age;
    bool publisher;
    string username;
    string email;
    string password;
public:
};

#endif