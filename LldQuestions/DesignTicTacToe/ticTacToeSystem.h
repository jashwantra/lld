#ifndef ticTacToeSystem_H
#define ticTacToeSystem_H 1

#include "game.h"
#include "observers/scoreboard.h"
#include "entities/player.h"
class TicTacToeSystem {
private:
    static TicTacToeSystem* instance;
    shared_ptr<Game> game;
    shared_ptr<Scoreboard> scoreboard;
    TicTacToeSystem();
    
public:
    static TicTacToeSystem* getInstance();
    
    void createGame(shared_ptr<Player> player1, shared_ptr<Player> player2);
    
    void makeMove(shared_ptr<Player> player, int row, int col) ;
    
    void printBoard() ;
    
    void printScoreBoard() ;
    
    ~TicTacToeSystem() {}
};

#endif