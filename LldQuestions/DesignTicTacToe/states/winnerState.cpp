#include "winnerState.h"
#include "exceptions/invalidMoveException.h"

void WinnerState :: handleMove(shared_ptr<Game> game, shared_ptr<Player> player, int row, int col) {
    throw InvalidMoveException("Game is already over. Winner has been determined.");
}


