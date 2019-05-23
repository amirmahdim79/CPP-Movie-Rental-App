#ifndef COMMENT_H_
#define COMMENT_H_

#include <string>
#include <vector>
#include "reply.h"

class Comment {
private:
    int id;
    int user_id;
    int film_id;
    std::string content;
    std::vector<Reply*> replies;
public:
    Comment(int id, int user_id, int film_id, std::string content);
    int get_id() {return id;}
    int get_user_id() {return id;}
    int get_film_id() {return film_id;}
    std::string get_content() {return content;}
    void add_reply(Reply* reply);
};

#endif