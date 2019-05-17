#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>

class Error {
protected:
public:
    virtual void show_message() = 0;
};

class UnknownCommand : public Error {
private:
public:
    void show_message();
};

class BadRequest : public Error {
private:
public:
    void show_message();
};

class PermissionDenied : public Error {
private:
public:
    void show_message();
};

class UserNotFound : public Error {
private:
public:
    void show_message();
};

#endif