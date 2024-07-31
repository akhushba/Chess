#include <iostream>
#include <vector>
#include<string>
#include<memory>

#include "boarddisplay.h"
using namespace std;
#include "piece.h"

int main () {

    BoardDisplay board_Display;

    string command;
    while (cin >> command) {
        try {
            if (command == "game" ) {
            string playerOne, playerTwo;
            cin >> playerOne >> playerTwo;
            board_Display.setPlayers(playerOne, playerTwo);

            string setup;
            cin >> setup;
                if (setup == "setup") {
                    board_Display.setUpGame();
                } else {
                    board_Display.defaultBoard();
                    command = setup;
                }
            }
            if (command == "resign") {
                BoardDisplay::PlayerInfo* currentPlayer = board_Display.getCurrentPlayer();
                board_Display.resign(currentPlayer->colour);
            }
            else if (command == "move") {
                BoardDisplay::PlayerInfo* currentPlayer= board_Display.getCurrentPlayer();
                board_Display.makeMove(currentPlayer->colour);
            } else if (command == "setup") {
                board_Display.setUpGame();
            }
        } catch (runtime_error& e) {
            board_Display.message = e.what();
            board_Display.notifyObservers();
        }
    }
    board_Display.endSession();
}


