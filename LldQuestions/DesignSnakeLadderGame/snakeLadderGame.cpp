#include <bits/stdc++.h>
using namespace std;

enum class GameStatus{
    NOT_STARTED,
    RUNNING,
    FINISHED
};

class Player{
private:
    string name;
    int position;
public:
    Player(string name_): name(name_), position(0){}
    string getName(){
        return name;
    } 
    int getPosition(){
        return position;
    }

    void setPosition(int newPosition){
        position=newPosition;
    }
};

class BoardEntity{
protected:
    int startPosition;
    int endPosition;

public:
    BoardEntity(int startPosition_, int endPosition_): startPosition(startPosition_), endPosition(endPosition_){}

    int getStartPosition(){
        return startPosition;
    }

    int getEndPosition(){
        return endPosition;
    }
};

class Snake : public BoardEntity {
public:
    Snake(int startPosition, int endPosition):BoardEntity(startPosition, endPosition){
        if(startPosition<=endPosition){
            throw std::invalid_argument("Snake head must be at a higher position than that of tail");
        }
    }
};

class Ladder : public BoardEntity {
public:
    Ladder(int startPosition, int endPosition):BoardEntity(startPosition, endPosition){
        if(startPosition>=endPosition){
            throw std::invalid_argument("Ladder start must be at a lower position than that of end");
        }
    }
};

class Dice{
private:
    int minValue;
    int maxValue;
public:
    Dice(int minValue_, int maxValue_): minValue(minValue_), maxValue(maxValue_){}

    int roll(){
        return minValue + (std::rand() % (maxValue-minValue+1));
    }
};

class Board{
private:
    int size;
    map<int,int> snakesAndLadder;
public:
    Board(int size_, vector<BoardEntity *> snakesAndLadders) : size(size_){
        for(auto & it: snakesAndLadders){
            snakesAndLadder[it->getStartPosition()] = it->getEndPosition();
        }
    }

    int getSize(){
        return size;
    }

    int getFinalPosition(int position){
        if(snakesAndLadder.find(position) != snakesAndLadder.end()){
            return snakesAndLadder[position];
        }
        return position;
    }
};

class Game {
public:
    class Builder;  // Forward declaration

private:
    std::unique_ptr<Board> board;
    std::queue<std::unique_ptr<Player>> players;
    std::unique_ptr<Dice> dice;
    GameStatus status;
    Player* winner;

    Game(Builder& builder)
        : board(std::move(builder.board)),
          players(std::move(builder.players)),
          dice(std::move(builder.dice)),
          status(GameStatus::NOT_STARTED),
          winner(nullptr) {}

    void takeTurn(Player* player) {
        cout<<"Press enter to roll for player "<<player->getName() <<" ";
        char userInput;
        userInput = getchar();

        if(userInput != '\n'){
            cout<<"Aborted by user";
            status = GameStatus::FINISHED;
            return ;
        }


        int roll = dice->roll();
        std::cout << std::endl << player->getName() << "'s turn. Rolled a " << roll << "." << std::endl;

        int currentPosition = player->getPosition();
        int nextPosition = currentPosition + roll;

        // Check if overshooting the board
        if (nextPosition > board->getSize()) {
            std::cout << "Oops, " << player->getName() << " needs to land exactly on "
                      << board->getSize() << ". Turn skipped." << std::endl;
            return;
        }

        // Check for win
        if (nextPosition == board->getSize()) {
            player->setPosition(nextPosition);
            winner = player;
            status = GameStatus::FINISHED;
            std::cout << "Hooray! " << player->getName() << " reached the final square "
                      << board->getSize() << " and won!" << std::endl;
            return;
        }

        // Apply snake or ladder if present
        int finalPosition = board->getFinalPosition(nextPosition);

        if (finalPosition > nextPosition) {
            std::cout << "Wow! " << player->getName() << " found a ladder at " << nextPosition
                      << " and climbed to " << finalPosition << "." << std::endl;
        } else if (finalPosition < nextPosition) {
            std::cout << "Oh no! " << player->getName() << " was bitten by a snake at " << nextPosition
                      << " and slid down to " << finalPosition << "." << std::endl;
        } else {
            std::cout << player->getName() << " moved from " << currentPosition
                      << " to " << finalPosition << "." << std::endl;
        }

        player->setPosition(finalPosition);

        // Extra turn for rolling 6
        if (roll == 6) {
            std::cout << player->getName() << " rolled a 6 and gets another turn!" << std::endl;
            takeTurn(player);
        }
    }


public:
    void play(){
        if(players.size() < 2){
            cout << "Cannot start game. At least 2 players are required." << std::endl;
            return;
        }

        status = GameStatus::RUNNING;
        std::cout << "Game started!" << std::endl;

        while (status == GameStatus::RUNNING) {
            // Get current player
            std::unique_ptr<Player> currentPlayer = std::move(players.front());
            players.pop();

            takeTurn(currentPlayer.get());

            if (status == GameStatus::RUNNING) {
                players.push(std::move(currentPlayer));
            }
        }

        std::cout << "Game Finished!" << std::endl;
        if (winner != nullptr) {
            std::cout << "The winner is " << winner->getName() << "!" << std::endl;
        }
    }

public:
    // Builder inner class
    class Builder {
    public:
        std::unique_ptr<Board> board;
        std::queue<std::unique_ptr<Player>> players;
        std::unique_ptr<Dice> dice;

        Builder& setBoard(int boardSize, const std::vector<BoardEntity*>& boardEntities) {
            board = std::make_unique<Board>(boardSize, boardEntities);
            return *this;
        }

        Builder& setPlayers(const std::vector<std::string>& playerNames) {
            for (const auto& name : playerNames) {
                players.push(std::make_unique<Player>(name));
            }
            return *this;
        }

        Builder& setDice(Dice* d) {
            dice = std::unique_ptr<Dice>(d);
            return *this;
        }

        std::unique_ptr<Game> build() {
            if (!board || players.empty() || !dice) {
                throw std::runtime_error("Board, Players, and Dice must be set.");
            }
            return std::unique_ptr<Game>(new Game(*this));
        }
    };

};

int main() {
    // Seed random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create board entities
    std::vector<BoardEntity*> boardEntities = {
        new Snake(17, 7),
        new Snake(54, 34),
        new Snake(62, 19),
        new Snake(98, 79),
        new Ladder(3, 38),
        new Ladder(24, 33),
        new Ladder(42, 93),
        new Ladder(72, 84)
    };

    // Create players
    std::vector<std::string> playerNames = {"Alice", "Bob", "Charlie"};

    // Build and play game
    auto game = Game::Builder()
        .setBoard(100, boardEntities)
        .setPlayers(playerNames)
        .setDice(new Dice(1, 6))
        .build();

    game->play();

    // Clean up board entities
    for (auto entity : boardEntities) {
        delete entity;
    }

    return 0;
}

