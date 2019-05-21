#include "program.h"
#include <iostream>
#include <vector>
#include <string>

#define QUESTIONMARK '?'
#define ASCII_A 'A'
#define ASCII_Z 'Z'
#define EMPTYSPACE ' '
#define EMPTYSTRING ""
#define NOTSET -1

void Program::increase_id() {
    this->id++;
}

void Program::increase_film_id() {
    this->film_id++;
}

int Program::character_location(string line, char character) {
    for (int i = 0; i < line.length(); i++)
        if (line[i] == character)
            return i;
}

int Program::find_user(int id) {
    if (id == -1) {
        Error* e = new PermissionDenied;
        throw e;
    }
    for (int i = 0; i < users.size(); i++) {
        if (id == users[i]->get_id())
            return i;
    }
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

void Program::check_username(string username) {
    for (int i = 0; i < usernames.size(); i++) {
        if (username == usernames[i]) {
            Error* e = new BadRequest;
            throw e;
        }
    }
}

void Program::check_user_exist(string username) {
    for (int i = 0; i < usernames.size(); i++) {
        if (username == usernames[i]) {
            return;
        }
    }
    Error* e = new UserNotFound;
    throw e;
}

void Program::check_access_publisher() {
    int user = find_user(active_user);
    if (users[user]->is_publisher() == false) {
        Error* e = new PermissionDenied;
        throw e;
    }
}

void Program::check_film_exists(int id) {
    for (int i = 0; i < all_films.size(); i++) {
        if (id == all_films[i]->get_id())
            return;
    }
    Error* e = new FilmNotFound;
    throw e;
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

void Program::read_username_password(string line, string &username, string &password) {
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "username")
            username = words[i + 1];
        if (words[i] == "password")
            password = words[i + 1];
    }
    if (username == "" || password == "") {
        Error* e = new BadRequest;
        throw e;
    }
}

void Program::delete_film_from_database(int id) {
    int selected_element;
    for (int i = 0; i < all_films.size(); i++) {
        if (id == all_films[i]->get_id())
            selected_element = i;
    }
    all_films.erase(all_films.begin() + selected_element);
}

void Program::do_command(string line, string method, string command) {
    if (command == "") {
        Error* e = new BadRequest;
        throw e;
    }
    if (method == "POST") {
        if (command == "signup")
            signup(line);
        if (command == "login") {
            string un, pass = "";
            read_username_password(line, un, pass);
            login(un, pass);
        }
        if (command == "films") {
            int user = find_user(active_user);
            check_access_publisher();
            add_film(line, user);
        }
        if (command == "followers") {
            int user = find_user(active_user);
            follow(line, user);
        }
        if (command == "money") {
            int user = find_user(active_user);
            add_money(line, user);
        }
    }
    else if (method == "GET") {
        if (command == "followers") {
            //show followers
        }
        if (command == "published") {
            int user = find_user(active_user);
            check_access_publisher();
            //
            show_published(line, user);
        }
    }
    else if (method == "PUT") {
        if (command == "films") {
            int user = find_user(active_user);
            check_access_publisher();
            edit_film(line, user);
        }
    }
    else if (method == "DELETE") {
        if (command == "films") {
            int user = find_user(active_user);
            check_access_publisher();
            delete_film(line, user);
        }
    }
}

void Program::signup(string line) {
    int age = NOTSET;
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
    check_username(username);
    if (username == "" || age == NOTSET || password == "" || email == "") {
        Error* e = new BadRequest;
        throw e;
    }
    User* user;
    if (publisher == false)
        user = new Customer(username, password, email, age, id);
    else
        user = new Publisher(username, password, email, age, id);
    increase_id();
    users.push_back(user);
    usernames.push_back(username);
    login(username, password);
}

void Program::login(string username, string password) {
    check_user_exist(username);
    for (int i = 0; i < users.size(); i++) {
        if (username == users[i]->get_username()) {
            if (password == users[i]->get_password()) {
                std::cout << "OK" << std::endl;
                active_user = users[i]->get_id();
            }
        }
    }
}

void Program::add_film(string line, int user) {
    int year = NOTSET;
    int length = NOTSET;
    int price = NOTSET;
    string name = EMPTYSTRING;
    string summary = EMPTYSTRING;
    string director = EMPTYSTRING;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "name")
            name = words[i + 1];
        if (words[i] == "summary")
            summary = words[i + 1];
        if (words[i] == "director")
            director = words[i + 1];
        if (words[i] == "year")
            year = stoi(words[i + 1]);
        if (words[i] == "length")
            length = stoi(words[i + 1]);
        if (words[i] == "price")
            price = stoi(words[i + 1]);
    }
    if (name == EMPTYSTRING || summary == EMPTYSTRING || director == EMPTYSTRING || year == NOTSET || length == NOTSET || price == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    //
    Film* film = new Film(year, length, price, name, summary, director, film_id);
    increase_film_id();
    std::cout << film_id << std::endl;
    all_films.push_back(film);
    users[user]->add_film(film);

    string fetched_id = to_string(users[user]->get_id());
    string message = "Publisher " + users[user]->get_username() + " with id " + fetched_id + " published film " + name;
    Notification* notif = new Notification(message);
    users[user]->send_notification_to_followers(notif);
    std::cout << "OK" << std::endl;
}

void Program::edit_film(string line, int user) {
    int film_id = NOTSET;
    int year = NOTSET;
    int length = NOTSET;
    int price = NOTSET;
    string name = EMPTYSTRING;
    string summary = EMPTYSTRING;
    string director = EMPTYSTRING;
    Film* film;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "film_id") {
            film_id = stoi(words[i + 1]);
            users[user]->has_film(film_id);
            film = users[user]->get_film(film_id);
        }
    }
    if (film_id == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    name = film->get_name();
    summary = film->get_summary();
    director = film->get_director();
    year = film->get_year();
    length = film->get_length();
    price = film->get_price();
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "name")
            name = words[i + 1];
        if (words[i] == "summary")
            summary = words[i + 1];
        if (words[i] == "director")
            director = words[i + 1];
        if (words[i] == "year")
            year = stoi(words[i + 1]);
        if (words[i] == "length")
            length = stoi(words[i + 1]);
        if (words[i] == "price")
            price = stoi(words[i + 1]);
    }
    film->set_name(name);
    film->set_director(director);
    film->set_length(length);
    film->set_price(price);
    film->set_summary(summary);
    film->set_year(year);
    std::cout << "OK" << std::endl;
}

void Program::delete_film(string line, int user) {
    int film_id = NOTSET;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++)
        if (words[i] == "film_id")
            film_id = stoi(words[i + 1]);
    if (film_id == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    check_film_exists(film_id);
    users[user]->has_film(film_id);
    delete_film_from_database(film_id);
    users[user]->delete_film(film_id);
}

void Program::show_published(string line, int user) {
    int min_year = NOTSET;
    int max_year = NOTSET;
    int price = NOTSET;
    double min_rate = NOTSET;
    string name = EMPTYSTRING;
    string director = EMPTYSTRING;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "name")
            name = words[i + 1];
        if (words[i] == "director")
            director = words[i + 1];
        if (words[i] == "min_year")
            min_year = stoi(words[i + 1]);
        if (words[i] == "max_year")
            max_year = stoi(words[i + 1]);
        if (words[i] == "price")
            price = stoi(words[i + 1]);
        if (words[i] == "min_rate")
            min_rate == stod(words[i + 1]);
    }
    if (name == EMPTYSTRING && director == EMPTYSTRING && min_year == NOTSET && max_year == NOTSET && price == NOTSET && min_rate == NOTSET) {
        users[user]->show_all_films();
        return;
    }
    vector<Film*> films = users[user]->get_films();
    if (name != EMPTYSTRING) {
       for (int i = 0; i < films.size(); i++) {
            if (films[i]->get_name() != name) {
                films.erase(films.begin() + i);
                i--;
            }
        } 
    }
    if (director != EMPTYSTRING) {
        for (int i = 0; i < films.size(); i++) {
            if (films[i]->get_director() != director) {
                films.erase(films.begin() + i);
                i--;
            }
        }
    }
    if (min_rate != NOTSET) {
        for (int i = 0; i < films.size(); i++) {
            if (films[i]->get_rate() < min_rate) {
                films.erase(films.begin() + i);
                i--;
            }
        }
    }
    if (price != NOTSET) {
        for (int i = 0; i < films.size(); i++) {
            if (films[i]->get_price() != price) {
                films.erase(films.begin() + i);
                i--;
            }
        }
    }
    if (max_year != NOTSET) {
        for (int i = 0; i < films.size(); i++) {
            if (films[i]->get_year() > max_year) {
                films.erase(films.begin() + i);
                i--;
            }
        }
    }
    if (min_year != NOTSET) {
        for (int i = 0; i < films.size(); i++) {
            if (films[i]->get_year() < min_year) {
                films.erase(films.begin() + i);
                i--;
            }
        }
    }

    std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
    for (int i = 0; i < films.size(); i++)
        std::cout << i + 1 << ". " << films[i]->get_id() << " | " << films[i]->get_name() << " | " << films[i]->get_length() << " | " << films[i]->get_price() << " | " << films[i]->get_rate() << " | " << films[i]->get_year() << " | " << films[i]->get_director() << std::endl;
}

void Program::follow(string line, int user) {
    int user_id = NOTSET;
    int follow_user_place = NOTSET;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "user_id")
            user_id = stoi(words[i + 1]);
    }
    for (int i = 0; i < users.size(); i++) {
        if (user_id == users[i]->get_id())
            follow_user_place = i;
    }
    if (user_id == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    if (follow_user_place == NOTSET) {
        Error* e = new UserNotFound;
        throw e;
    }
    users[user]->follow(users[follow_user_place]);
    users[follow_user_place]->add_to_followers(users[user]);

    string fetched_id = to_string(users[user]->get_id());
    string message = "User " + users[user]->get_username() + " with id " + fetched_id + " follow you.";
    Notification* notif = new Notification(message);
    users[user_id]->add_to_notifications(notif);

    std::cout << "OK" << std::endl;
}

void Program::add_money(string line, int user) {
    int amount = NOTSET;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "amount")
            amount = stoi(words[i + 1]);
    }
    if (amount == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    users[user]->increase_money(amount);
    std::cout << "OK" << std::endl;
}