#ifndef gameSubject_H
#define gameSubject_H 1


#include "gameObserver.h"
#include <vector>
#include <memory>
class GameSubject {
private:
    std::vector<std::shared_ptr<GameObserver>> observers;
    
public:
    void addObserver(std::shared_ptr<GameObserver> observer) ;
    
    void removeObserver(std::shared_ptr<GameObserver> observer) ;
    
    void notifyObservers(std::shared_ptr<Game> game);
};

#endif