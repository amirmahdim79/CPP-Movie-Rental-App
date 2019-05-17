#ifndef USER_H_
#define USER_H_

#include <string>
using namespace std;

class User {
protected:
    int id;
    int age;
    string username;
    string email;
    string password;
    bool publisher;
public:
    int get_id();
    string get_password();
    string get_username();
};

#endif