#ifndef game_H
#define game_H 1

#include "entities/board.h"
#include "entities/player.h"
#include "states/gameState.h"
#include "enums/gameStatus.h"
#include "strategies/winningStrategy.h"
#include "observers/gameSubject.h"
#include <memory>
#include <vector>

class Game : public GameSubject {
    private:
    std::shared_ptr<Board> board;
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    std::shared_ptr<GameState> gameState;
    std::shared_ptr<Player> currentPlayer;
    std::shared_ptr<Player> winner;
    GameStatus gameStatus;
    std::vector<std::shared_ptr<WinningStrategy>> winningStrategies;

    public:
    Game(std::shared_ptr<Player>, std::shared_ptr<Player>) ;
    ~Game();

    void makeMove(std::shared_ptr<Game> game, std::shared_ptr<Player> player, int row, int col) ;
    
    bool checkWinner(std::shared_ptr<Player> player);

    void switchPlayer();

    std::shared_ptr<Board> getBoard();
    std::shared_ptr<Player> getCurrentPlayer();
    std::shared_ptr<Player> getWinner();

    void setWinner(std::shared_ptr<Player>);
    GameStatus getStatus();
    void setStatus(GameStatus);
    void setState(shared_ptr<GameState> newState);

};

#endif