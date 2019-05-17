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

int Program::character_location(string line, char character) {
    for (int i = 0; i < line.length(); i++)
        if (line[i] == character)
            return i;
}

vector<string> Program::break_to_words(string line) {
    string word = "";
    vector<string> words;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == ' ') {
            words.push_back(word);
            word = "";
            continue;
        }
        word = word + line[i];
        if (i == line.length() - 1)
            words.push_back(word);
    }
    return words;
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

void Program::check_command(string command) {
    int ok = 0;
    for (int i = 0; i < this->commands.size(); i++) {
        if (command == commands[i])
            ok = 1;
    }
    if (ok != 1) {
        Error* e = new UnknownCommand;
        throw e;
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
    check_command(command);
    do_command(line, method, command);
}

void Program::do_command(string line, string method, string command) {
    if (command == "") {
        Error* e = new BadRequest;
        throw e;
    }
    if (method == "POST") {
        if (command == "signup")
            signup(line);
    }
    else if (method == "GET") {

    }
    else if (method == "PUT") {

    }
    else if (method == "DELETE") {
        
    }
}

void Program::signup(string line) {
    int age = 1000;
    string username = "";
    string password = "";
    string email = "";
    bool publisher = false;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "username")
            username = words[i + 1];
        if (words[i] == "password")
            password = words[i + 1];
        if (words[i] == "age")
            age = stoi(words[i + 1]);
        if (words[i] == "email")
            email = words[i + 1];
        if (words[i] == "publisher") {
            if (words[i + 1] == "true")
                publisher = true;
        }
    }
    if (username == "" || age == 1000 || password == "" || email == "") {
        Error* e = new BadRequest;
        throw e;
    }
    User* user;
    if (publisher == false)
        user = new Customer(username, password, email, age, id);
    else
        user = new Publisher(username, password, email, age, id);
    increase_id();
}