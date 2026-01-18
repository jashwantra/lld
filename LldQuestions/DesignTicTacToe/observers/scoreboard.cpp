#include "scoreboard.h"
#include <iostream>
using namespace std;

void Scoreboard:: update(shared_ptr<Game> game) {
    ;//TODO
}

void Scoreboard:: printScores(){
    cout << endl << "--- Overall Scoreboard ---" << endl;
    if(scores.empty()) {
        cout << "No games with a winner have been played yet." << endl;
        return;
    }
    for(auto& pair : scores) {
        cout << "Player: " << pair.first << " | Wins: " << pair.second << endl;
    }
    cout << "--------------------------" << endl << endl;
}
