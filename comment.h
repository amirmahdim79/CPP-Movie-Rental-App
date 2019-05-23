#ifndef COMMENT_H_
#define COMMENT_H_

#include <string>

class Comment {
private:
    int id;
    int user_id;
    int film_id;
    std::string content;
public:
    Comment(int id, int user_id, int film_id, std::string content);
    int get_id() {return id;}
    int get_user_id() {return id;}
    int get_film_id() {return film_id;}
    std::string get_content() {return content;}
};

#endif