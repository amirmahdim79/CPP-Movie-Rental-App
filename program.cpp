#include "program.h"
#include <iostream>
#include <vector>
#include <string>

#define QUESTIONMARK '?'
#define ASCII_A 'A'
#define ASCII_Z 'Z'
#define EMPTYSPACE ' '

void Program::increase_id() {
    this->id++;
}

void Program::run() {
    bool program_running = true;
    while (program_running) {
        try {
            this->get_command();
        }
        catch (Error *e) {
            e->show_message();
        }
    }
}

void Program::get_command() {
    string line;
    getline(cin, line);
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ')
            if (line[i + 1] == ' ') {
                line.erase(i, 1);
                i--;
            }
    }
    this->break_command(line);
}

void Program::break_command(string line) {
    string full_command = "";
    for (int i = 0; i < line.length(); i++) {
        full_command = full_command + line[i];
        if (line[i] == '?' || i == line.length() - 1) {
            int last_letter = full_command.size() - 1;
            if (full_command[last_letter] == '?') 
                full_command.erase(last_letter, 1);
            read_method_command(line, full_command);
            break;
        }
    }
}

void Program::read_method_command(string line, string full_command) {
    string method = "";
    string command = "";
    for (int i = 0; i < full_command.length(); i++) {
        if (full_command[i] == EMPTYSPACE)
            continue;
        if (full_command[i] >= ASCII_A && full_command[i] <= ASCII_Z)
            method = method + full_command[i];
        else
            command = command + full_command[i];
    }
    check_method(method);
    analyse_method(line, method, command);
}

void Program::analyse_method(string line, string method, string command) {
    
}

void Program::check_method(string method) {
    int ok = 0;
    for (int i = 0; i < this->methods.size(); i++) {
        if (method == methods[i])
            ok = 1;
    }
    if (ok != 1) {
        Error* e = new BadRequest;
        throw e;
    }
}