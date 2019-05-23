#ifndef REPLY_H_
#define REPLY_H_

#include <string>

class Reply {
private:
    int user_id;
    int comment_id;
    std::string content;
public:
    Reply(int user_id, int commnet_id, std::string content);
};

#endif