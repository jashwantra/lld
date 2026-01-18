#include "ticTacToeSystem.h"
#include "exceptions/invalidMoveException.h"
#include <iostream>

using namespace std;

TicTacToeSystem::TicTacToeSystem() : game(NULL), scoreboard(make_shared<Scoreboard>()) {}

TicTacToeSystem* TicTacToeSystem::getInstance() {
    if(instance == NULL) {
        instance = new TicTacToeSystem();
    }
    return instance;
}

void TicTacToeSystem::createGame(shared_ptr<Player> player1, shared_ptr<Player> player2) {
    if(game != NULL) {
        game = NULL;
    }
    game = make_shared<Game>(player1, player2);
    game->addObserver(scoreboard);
    
    cout << "Game started between " << player1->getName() << " (X) and " 
            << player2->getName() << " (O)." << endl;
}

void TicTacToeSystem::makeMove(shared_ptr<Player> player, int row, int col) {
    if(game == nullptr) {
        cout << "No game in progress. Please create a game first." << endl;
        return;
    }
    try {
        cout << player->getName() << " plays at (" << row << ", " << col << ")" << endl;
        game->makeMove(game, player, row, col);
        printBoard();
        cout << "Game Status: " << game->getStatus() << endl;
        if(game->getWinner() != nullptr) {
            cout << "Winner: " << game->getWinner()->getName() << endl;
        }
    } catch(const InvalidMoveException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void TicTacToeSystem::printBoard() {
    game->getBoard()->printBoard();
}

void TicTacToeSystem::printScoreBoard() {
    scoreboard->printScores();
}

TicTacToeSystem* TicTacToeSystem::instance = NULL;