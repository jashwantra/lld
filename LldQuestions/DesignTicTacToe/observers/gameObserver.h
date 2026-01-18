#ifndef gameObserver_H
#define gameObserver_H 1

#include <memory>

class Game;

class GameObserver {
public:
    virtual ~GameObserver() = default;
    virtual void update(std::shared_ptr<Game> game) = 0;
};

#endif