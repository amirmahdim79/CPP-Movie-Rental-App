#include "reply.h"

Reply::Reply(int user_id, int commnet_id, std::string content) {
    this->user_id = user_id;
    this->comment_id = comment_id;
    this->content = content;
}

std::string Reply::get_content() {
    return content;
} 