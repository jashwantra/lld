#include "invalidMoveException.h"

InvalidMoveException :: InvalidMoveException(const char *msg) : message(msg){}

const char* InvalidMoveException :: what() const noexcept {
    return message;
}


