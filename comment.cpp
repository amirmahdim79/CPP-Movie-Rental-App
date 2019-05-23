#include "comment.h"

Comment::Comment(int id, int user_id, int film_id, std::string content) {
    this->id = id;
    this->user_id = user_id;
    this->film_id = film_id;
    this->content = content;
}
