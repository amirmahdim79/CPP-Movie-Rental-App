#include "program.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define QUESTIONMARK '?'
#define SIGNUP "POSTsignup"

void Program::increase_id() {
    this->id++;
}

void Program::get_command() {
    string line;
    getline(cin, line);
    for (int i = 0; i < line.length(); i++) {
        if (line[i] = ' ') {
            line.erase(i, 1);
        }
    }
    this->analyse_command(line);
}

void Program::analyse_command(string line) {
    string command = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '?') {
            analyse_command_line(line, command);
            break;
        }
        command = command + line[i];
    }
}

void Program::analyse_command_line(string line, string command) {

}