#include "gameSubject.h"

using namespace std;

void GameSubject::addObserver(shared_ptr<GameObserver> gameObserver){
    observers.push_back(gameObserver);
}

void GameSubject::removeObserver(shared_ptr<GameObserver> gameObserver){
    for(auto it = observers.begin(); it != observers.end(); ++it) {
        if(*it == gameObserver) {
            observers.erase(it);
            break;
        }
    }
}


void GameSubject::notifyObservers(shared_ptr<Game> game) {
    for (shared_ptr<GameObserver> & observer : observers) {
        observer->update(game);
    }
}
