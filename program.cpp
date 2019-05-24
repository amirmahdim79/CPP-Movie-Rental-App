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

Film* Program::get_film(int film_id) {
    for (int i = 0; i < all_films.size(); i++) {
        if (film_id == all_films[i]->get_id()) {
            return all_films[i];
        }
    }
}

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

void Program::add_money_to_server(Money* money) {
    money_server.push_back(money);
}

void Program::do_command(string line, string method, string command) {
    if (command == "") {
        Error* e = new BadRequest;
        throw e;
    }
    if (method == "POST") {
        if (command == "signup") {
            if (active_user == -1)
                signup(line);
            else {
                Error* e = new BadRequest;
                throw e;
            }

        }
        if (command == "login") {
            if (active_user == -1) {
                string un, pass = "";
                read_username_password(line, un, pass);
                login(un, pass);
            }
            else {
                Error* e = new BadRequest;
                throw e;
            }
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
        if (command == "buy") {
            int user = find_user(active_user);
            buy_film(line, user);
        }
        if (command == "rate") {
            int user = find_user(active_user);
            rate_film(line, user);
        }
        if (command == "comments") {
            int user = find_user(active_user);
            comment_on_film(line, user);
        }
        if (command == "replies") {
            int user = find_user(active_user);
            check_access_publisher();
            add_reply(line, user);
        }
        if (command == "put_films") {
            int user = find_user(active_user);
            check_access_publisher();
            edit_film(line, user);
        }
        if (command == "delete_film") {
            int user = find_user(active_user);
            check_access_publisher();
            delete_film(line, user);
        }
        if (command == "delete_comments") {
            int user = find_user(active_user);
            check_access_publisher();   
            delete_comment(line, user);
        }
        if (command == "logout") {
            active_user = NOTSET;
            std::cout << "OK" << std::endl;
        }
    }
    else if (method == "GET") {
        if (command == "followers") {
            int user = find_user(active_user);
            check_access_publisher();
            users[user]->show_followers();
        }
        if (command == "published") {
            int user = find_user(active_user);
            check_access_publisher();
            //
            show_published(line, user);
        }
        if (command == "put_films") {
            int user = find_user(active_user);
            search_films(line, user);
        }
        if (command == "purchased") {
            int user = find_user(active_user);
            show_purchased(line, user);
        }
        if (command == "notifications") {
            int user = find_user(active_user);
            show_notifications(line, user);
        }
        if (command == "notificationsread") {
            int user = find_user(active_user);
            show_read_notifications(line, user);
        }
        if (command == "money") {
            int user = find_user(active_user);
            std::cout << users[user]->get_money() << std::endl;
        }
    }
    else if (method == "PUT") {
        
    }
    else if (method == "DELETE") {
        
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
    Film* film = new Film(year, length, price, name, summary, director, film_id, users[user]->get_id());
    increase_film_id();
    all_films.push_back(film);
    users[user]->add_film(film);

    string fetched_id = to_string(users[user]->get_id());
    string message = "Publisher " + users[user]->get_username() + " with id " + fetched_id + " register new film.";
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
    users[user_id - 1]->add_to_notifications(notif);

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
        if (users[user]->is_publisher() == false) {
            Error* e = new BadRequest;
            throw e;
        }
        else {
            vector<Film*> films;
            films = users[user]->get_films();
            vector<Money*> earnings;
            int earned_amount;
            int server_earned;
            for (int i = 0; i < money_server.size(); i++) {
                if (money_server[i]->active == 0) {
                    continue;
                }
                if (users[user]->get_id() == money_server[i]->publisher_id) {
                    earnings.push_back(money_server[i]);
                }
            }
            for (int i = 0; i < earnings.size(); i++) {
                for (int j = 0; j < films.size(); j++) {
                    if (earnings[i]->get_film_id() == films[j]->get_id()) {
                        double rate = films[j]->get_rate();
                        int money = earnings[i]->get_amount();
                        if (rate < 5) {
                            double persend = 80 / 100;
                            earned_amount = money * persend;
                            server_earned = money - earned_amount;
                            server_earnings.push_back(earnings[i]);
                            earnings[i]->active = 0;
                            users[user]->increase_money(earned_amount);
                            all_money = all_money + server_earned;
                        }
                        if (rate >= 5 && rate < 8) {
                            double persend = 90 / 100;
                            earned_amount = money * persend;
                            server_earned = money - earned_amount;
                            server_earnings.push_back(earnings[i]);
                            earnings[i]->active = 0;
                            users[user]->increase_money(earned_amount);
                            all_money = all_money + server_earned;
                        }
                        if (rate >= 8) {
                            double persend = 95 / 100;
                            earned_amount = money * persend;
                            server_earned = money - earned_amount;
                            server_earnings.push_back(earnings[i]);
                            earnings[i]->active = 0;
                            users[user]->increase_money(earned_amount);
                            all_money = all_money + server_earned;
                        }
                    }
                }
            }
        }
        std::cout << "OK" << std::endl;
        return;
    }
    else {
        users[user]->increase_money(amount);
        std::cout << "OK" << std::endl;
    }
}

void Program::search_films(string line, int user) {
    int film_id = NOTSET;
    int min_year = NOTSET;
    int max_year = NOTSET;
    int price = NOTSET;
    double min_rate = NOTSET;
    string name = EMPTYSTRING;
    string director = EMPTYSTRING;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "film_id")
            film_id = stoi(words[i + 1]);
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
    vector<Film*> films = all_films;
    if (film_id != NOTSET) {
        film_details(film_id);
        show_comments_and_replies(film_id);
        show_recommendation_films(film_id);
        return;
    }
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

void Program::buy_film(string line, int user) {
    int film_id = NOTSET;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "film_id")
            film_id = stoi(words[i + 1]);
    }
    if (film_id == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    //check if film exists
    //check if film is duplicate
    Film* film;
    film = this->get_film(film_id);
    users[user]->decrese_money(film->get_price());
    users[user]->buy_film(film);
    Money* money = new Money(film->get_price(), film->get_publisher_id(), film->get_id());
    add_money_to_server(money);
    string message = "User " + users[user]->get_username() + " with id " + to_string(users[user]->get_id()) + " buy your film " + film->get_name() + " with id " + to_string(film->get_id());
    Notification* notif = new Notification(message);
    users[film->get_publisher_id() - 1]->add_to_notifications(notif);
    std::cout << "OK" << std::endl;
}

void Program::rate_film(string line, int user) {
    int film_id = NOTSET;
    int score = NOTSET;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "film_id")
            film_id = stoi(words[i + 1]);
        if (words[i] == "score")
            score = stoi(words[i + 1]);
    }
    Film* film;
    film = this->get_film(film_id);
    //check if rate is 1 to 10
    //check if rate is not duplicate
    Rate* rate = new Rate(score, users[user]->get_id(), film_id);
    film->set_ratings(rate);
    string message = "User " + users[user]->get_username() + " with id " + to_string(users[user]->get_id()) + " rate your film " + film->get_name() + " with id " + to_string(film->get_id());
    Notification* notif = new Notification(message);
    users[film->get_publisher_id() - 1]->add_to_notifications(notif);
    std::cout << "OK" << std::endl;
}

void Program::comment_on_film(string line, int user) {
    int film_id = NOTSET;
    std::string content = EMPTYSTRING;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "film_id")
            film_id = stoi(words[i + 1]);
        if (words[i] == "content")
            content = words[i + 1];
    }
    if (film_id == NOTSET || content == EMPTYSTRING) {
        Error* e = new BadRequest;
        throw e;
    }
    //check film exists
    Film* film;
    film = get_film(film_id);
    Comment* comment = new Comment(film->get_comment_id(), users[user]->get_id(), film->get_id(), content);
    film->set_comment(comment);
    film->increase_comment_id();
    string message = "User " + users[user]->get_username() + " with id " + to_string(users[user]->get_id()) + " comment on your film " + film->get_name() + " with id " + to_string(film->get_id());
    Notification* notif = new Notification(message);
    users[film->get_publisher_id() - 1]->add_to_notifications(notif);
    std::cout << "OK" << std::endl;
}

void Program::show_purchased(string line, int user) {
    int min_year = NOTSET;
    int max_year = NOTSET;
    int price = NOTSET;
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
    }

    vector<Film*> temp;
    temp = users[user]->get_bought_films();
    int smallest_film = 0;
    vector<Film*> sorted_films;
    while(1) {
        if (temp.size() == 0)
            break;
        for (int i = 1; i < temp.size(); i++) {
            if (i == temp.size())
                break;
            if (temp[smallest_film]->get_id() > temp[i]->get_id()) {
                smallest_film = i;
            }
        }
        sorted_films.push_back(temp[smallest_film]);
        temp.erase(temp.begin() + smallest_film);
        smallest_film = 0;
    }

    if (name != EMPTYSTRING) {
       for (int i = 0; i < sorted_films.size(); i++) {
            if (sorted_films[i]->get_name() != name) {
                sorted_films.erase(sorted_films.begin() + i);
                i--;
            }
        } 
    }
    if (director != EMPTYSTRING) {
        for (int i = 0; i < sorted_films.size(); i++) {
            if (sorted_films[i]->get_director() != director) {
                sorted_films.erase(sorted_films.begin() + i);
                i--;
            }
        }
    }
    if (price != NOTSET) {
        for (int i = 0; i < sorted_films.size(); i++) {
            if (sorted_films[i]->get_price() != price) {
                sorted_films.erase(sorted_films.begin() + i);
                i--;
            }
        }
    }
    if (max_year != NOTSET) {
        for (int i = 0; i < sorted_films.size(); i++) {
            if (sorted_films[i]->get_year() > max_year) {
                sorted_films.erase(sorted_films.begin() + i);
                i--;
            }
        }
    }
    if (min_year != NOTSET) {
        for (int i = 0; i < sorted_films.size(); i++) {
            if (sorted_films[i]->get_year() < min_year) {
                sorted_films.erase(sorted_films.begin() + i);
                i--;
            }
        }
    }

    std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
    for (int i = 0; i < sorted_films.size(); i++)
        std::cout << i + 1 << ". " << sorted_films[i]->get_id() << " | " << sorted_films[i]->get_name() << " | " << sorted_films[i]->get_length() << " | " << sorted_films[i]->get_price() << " | " << sorted_films[i]->get_rate() << " | " << sorted_films[i]->get_year() << " | " << sorted_films[i]->get_director() << std::endl;
    
}

void Program::show_notifications(string line, int user) {
    users[user]->show_notifications();
    users[user]->add_to_read_notifications();
    users[user]->delete_notifications();
}

void Program::show_read_notifications(string line, int user) {
    int limit = NOTSET;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "limit")
            limit = stoi(words[i + 1]);
    }
    if (limit == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    users[user]->show_read_notifications(limit);
}

void Program::film_details(int film_id) {
    Film* film;
    film = this->get_film(film_id);
    std::cout << "Details of Film " << film->get_name() << std::endl;
    std::cout << "Id = " << film->get_id() << std::endl;
    std::cout << "Director = " << film->get_director() << std::endl;
    std::cout << "Length = " << film->get_length() << std::endl;
    std::cout << "Year = " << film->get_year() << std::endl;
    std::cout << "Summary = " << film->get_summary() << std::endl;
    std::cout << "Rate = " << film->get_rate() << std::endl;
    std::cout << "Price = " << film->get_price() << std::endl << std::endl;
}

void Program::show_comments_and_replies(int film_id) {
    Film* film;
    film = this->get_film(film_id);
    vector<Comment*> comments;
    comments = film->get_comments();
    std::cout << "Comments" << std::endl; 
    for (int i = 0; i < comments.size(); i++) {
        vector<Reply*> replies;
        replies = comments[i]->get_replies();
        std::cout << comments[i]->get_id() << ". " << comments[i]->get_content() << std::endl;
        for (int j = 0; j < replies.size(); j++) {
            std::cout << comments[i]->get_id() << "." << j + 1 << ". " << replies[j]->get_content() << std::endl;
        }
    }
    std::cout << std::endl;
}

void Program::show_recommendation_films(int film_id) {
    std::cout << "Recommendation Film" << std::endl;
    std::cout << "#. Film Id | Film Name | Film Length | Film Director" << std::endl;
    Film* film;
    film = this->get_film(film_id);
    vector<Film*> films = all_films;
    vector<Film*> recommended_films;
    for (int i = 0; i < 4; i++) {
        int max = 0;
        for (int j = 0; j < films.size(); j++) {
            if (films[max]->get_rate() < films[j]->get_rate())
                max = j;
        }
        recommended_films.push_back(films[max]);
        films.erase(films.begin() + max);
        max = 0;
    }
    for (int i = 0; i < films.size(); i++) {
        std::cout << i + 1 << ". " << films[i]->get_id() << " | " << films[i]->get_name() << " | " << films[i]->get_length() << " | " << films[i]->get_director() << std::endl;
    }
}

void Program::add_reply(string line, int user) {
    int film_id = NOTSET;
    int comment_id = NOTSET;
    std::string content = EMPTYSTRING;
    vector<std::string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "film_id")
            film_id = stoi(words[i + 1]);
        if (words[i] == "comment_id")
            comment_id = stoi(words[i + 1]);
        if (words[i] == "content")
            content = words[i + 1];
    }
    if (film_id == NOTSET || comment_id == NOTSET || content == EMPTYSTRING) {
        Error* e = new BadRequest;
        throw e;
    }
    Film* film;
    users[user]->has_film(film_id);
    film = users[user]->get_film(film_id);
    Reply* reply = new Reply(users[user]->get_id(), comment_id, content);
    Comment* comment;
    comment = film->get_comment(comment_id);
    comment->add_reply(reply);
    string message = "Publisher " + users[user]->get_username() + " with id " + to_string(users[user]->get_id()) + " reply to your comment";
    Notification* notif = new Notification(message);
    users[comment->get_user_id() - 1]->add_to_notifications(notif);
    std::cout << "OK" << std::endl;
}

void Program::delete_comment(string line, int user) {
    int film_id = NOTSET;
    int comment_id = NOTSET;
    vector<string> words = break_to_words(line);
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "film_id")
            film_id = stoi(words[i + 1]);
        if(words[i] == "comment_id")
            comment_id = stoi(words[i + 1]);
    }
    if (film_id == NOTSET || comment_id == NOTSET) {
        Error* e = new BadRequest;
        throw e;
    }
    Film* film;
    users[user]->has_film(film_id);
    film = users[user]->get_film(film_id);
    film->delete_comment(comment_id);
    std::cout << "OK" << std::endl;
}