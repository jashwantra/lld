#include "ticTacToeSystem.h"
#include <iostream>
#include <memory>
using namespace std;
class TicTacToeDemo {
public:
    static void main() {
        TicTacToeSystem* system = TicTacToeSystem::getInstance();
        
        shared_ptr<Player> alice = make_shared<Player>("Alice", X);
        shared_ptr<Player> bob = make_shared<Player>("Bob", O);
        
        // GAME 1: Alice wins
        cout << "--- GAME 1: Alice (X) vs. Bob (O) ---" << endl;
        system->createGame(alice, bob);
        system->printBoard();
        
        system->makeMove(alice, 0, 0);
        system->makeMove(bob, 1, 0);
        system->makeMove(alice, 0, 1);
        system->makeMove(bob, 1, 1);
        system->makeMove(alice, 0, 2); // Alice wins
        cout << "----------------------------------------" << endl << endl;
        
        // GAME 2: Bob wins
        cout << "--- GAME 2: Alice (X) vs. Bob (O) ---" << endl;
        system->createGame(alice, bob);
        system->printBoard();
        
        system->makeMove(alice, 0, 0);
        system->makeMove(bob, 1, 0);
        system->makeMove(alice, 0, 1);
        system->makeMove(bob, 1, 1);
        system->makeMove(alice, 2, 2);
        system->makeMove(bob, 1, 2); // Bob wins
        cout << "----------------------------------------" << endl << endl;
        
        // GAME 3: A Draw
        cout << "--- GAME 3: Alice (X) vs. Bob (O) - Draw ---" << endl;
        system->createGame(alice, bob);
        system->printBoard();
        
        system->makeMove(alice, 0, 0);
        system->makeMove(bob, 0, 1);
        system->makeMove(alice, 0, 2);
        system->makeMove(bob, 1, 1);
        system->makeMove(alice, 1, 0);
        system->makeMove(bob, 1, 2);
        system->makeMove(alice, 2, 1);
        system->makeMove(bob, 2, 0);
        system->makeMove(alice, 2, 2); // Draw
        cout << "----------------------------------------" << endl << endl;
        
        // Final Scoreboard
        system->printScoreBoard();

        delete system;
    }
};

int main() {
    TicTacToeDemo::main();
    return 0;
}