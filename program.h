#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>

#include "user.h"
#include "publisher.h"
#include "customer.h"

using namespace std;

class Program {
private:
    int id = 0;
public:
    void increase_id();
    void get_command();
    void analyse_command(string line);
    void analyse_command_line(string line, string command);
};

#endif