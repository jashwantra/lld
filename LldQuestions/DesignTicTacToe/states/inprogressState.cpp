#include "inprogressState.h"
#include "exceptions/invalidMoveException.h"
#include "game.h"
#include "winnerState.h"
#include "drawState.h"
#include <iostream>

void InProgressState::handleMove(shared_ptr<Game> game, shared_ptr<Player> player, int row, int col) {
    if(game->getCurrentPlayer() != player){
        throw InvalidMoveException("Not your turn!");
    }

    try{
        game->getBoard()->placeSymbol(row, col, player->getSymbol());
    }catch(InvalidMoveException& e){
        cout<<"Runtime error : "<<e.what()<<"\n";
        return ;
    }

    if(game->checkWinner(player)) {
        game->setWinner(player);
        game->setStatus(player->getSymbol() == Symbol::X ? WINNER_X : WINNER_O);
        game->setState(make_shared<WinnerState>());
    } else if(game->getBoard()->isFull()) {
        game->setStatus(DRAW);
        game->setState(make_shared<DrawState>());
    } else {
        game->switchPlayer();
    }
    
}
