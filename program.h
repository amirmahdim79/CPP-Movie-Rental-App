#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>
#include <vector>

#include "user.h"
#include "publisher.h"
#include "customer.h"
#include "exceptions.h"

using namespace std;

class Program {
private:
    int id = 0;
    vector<string> methods = {"GET", "PUT", "POST", "DELETE"};
    vector<string> commands = {"signup", "login", "films", "followers", "money", "published",
                                "replise", "comments", "followers", "buy", "rate", "purchased",
                                "notifications", "notificationsread"};
public:
    void run();

    void increase_id();
    void break_command(string line);
    void read_method_command(string line, string command);

    void check_method(string method);
    void check_command(string command);

    void get_command();
    void analyse_method(string line, string method, string command);
    void analyse_command(string line, string command);
};

#endif