#ifndef invalidMoveException_H
#define invalidMoveException_H 1

#include <exception>

class InvalidMoveException : public std::exception {
private:
    const char* message;
public:
    InvalidMoveException(const char* msg) ;
    const char* what() const noexcept override;
};

#endif