#ifndef scoreboard_H
#define scoreboard_H 1

#include "gameObserver.h"
#include <map>
#include <memory>

class Scoreboard : public GameObserver {
private:
    std::map<std::string, int> scores;
public:
    void update(std::shared_ptr<Game> game) override;
    
    void printScores();
};

#endif