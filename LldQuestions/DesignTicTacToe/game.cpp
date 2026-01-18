#include "game.h"
#include "exceptions/invalidMoveException.h"
#include "states/inProgressState.h"
#include "strategies/rowWinningStrategy.h"
#include "strategies/columnWinningStrategy.h"
#include "strategies/diagonalWinningStrategy.h"
#include <iostream>

using namespace std;

Game :: Game(std::shared_ptr<Player> player1_, std::shared_ptr<Player>player2_) : 
        player1(player1_), player2(player2_), board(make_shared<Board>(3)), 
        gameState(make_shared<InProgressState>()), currentPlayer(player1),
        winner(NULL), gameStatus(GameStatus::IN_PROGRESS) {
        winningStrategies.push_back(make_shared<RowWinningStrategy>());
        winningStrategies.push_back(make_shared<ColumnWinningStrategy>());
        winningStrategies.push_back(make_shared<DiagonalWinningStrategy>());
}
    
Game :: ~Game(){}

void Game::makeMove(shared_ptr<Game> game, shared_ptr<Player> player, int row, int col){
    try{
        gameState->handleMove(game ,player, row, col);
    }catch(InvalidMoveException& e){
        cout<<"Runtime error: "<<e.what()<<"\n";
    }
}

bool Game::checkWinner(shared_ptr<Player> player){
    for(shared_ptr<WinningStrategy> & strategy : winningStrategies){
        if(strategy->checkWinner(board, player)){
            return true;
        }
    }
    return false;
}

void Game::switchPlayer(){
    currentPlayer = (currentPlayer == player1) ? player2 : player1 ;
}

shared_ptr<Board> Game::getBoard(){
    return board;
}

shared_ptr<Player> Game::getCurrentPlayer(){
    return currentPlayer;
}

shared_ptr<Player> Game :: getWinner(){
    return winner;
}

void Game::setWinner(shared_ptr<Player> player){
    winner = player;
}

GameStatus Game::getStatus(){
    return gameStatus;
}

void Game::setStatus(GameStatus status){
    gameStatus = status;
}

void Game::setState(shared_ptr<GameState> newState) { 
    gameState = move(newState); 
}
