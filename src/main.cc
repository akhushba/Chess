#include <iostream>
#include <vector>
#include<string>
#include<memory>

#include "boarddisplay.h"
using namespace std;
#include "piece.h"

int main () {

    BoardDisplay board_Display;
    // board_Display.defaultBoard();
    // board_Display.notifyObservers();
    // Piece* p  = board_Display.getBoardInfo('a', 2);
    // cout << board_Display.checkValid(p, 'a', 3) << endl;


    string command;
    while (cin >> command) {
    if (command == "game" ) {
        cout << "game cmd start" << endl;
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
        cout << "game cmd end" << endl;
    }
    
    if (command == "resign") {
        BoardDisplay::PlayerInfo* currentPlayer = board_Display.getCurrentPlayer();
        board_Display.resign(currentPlayer->colour);
    }
    else if (command == "move") {
        cout << "move cmd start" << endl;
        string oldPos, newPos;
        cin >> oldPos >> newPos;
        BoardDisplay::PlayerInfo* currentPlayer= board_Display.getCurrentPlayer();
        if (currentPlayer->colour == WHITE) { cout << "white" << endl; }
        if (currentPlayer->colour == BLACK) { cout << "black" << endl; }
        board_Display.makeMove(currentPlayer->colour, oldPos, newPos);
        board_Display.getCurrentTurn = currentPlayer->colour == WHITE ? BLACK : WHITE;
        // cout << "------1" << endl;
        // if(currentPlayer-> colour == WHITE) {
        //     board_Display.inCheck(board_Display.getBlackPlayer()->colour);
        // }
        // cout << "------2" << endl;
        // if(currentPlayer-> colour == BLACK) {
        //     board_Display.inCheck(board_Display.getWhitePlayer()->colour);
        // }
        // cout << "------3" << endl;
        // if(board_Display.inStalemate(Colour:: WHITE) || board_Display.inStalemate(Colour:: BLACK)){
        //     //update score
        //     //endgame
        //     board_Display.getWhitePlayer()->score += 0.5;
        //     board_Display.getBlackPlayer()->score += 0.5;
        //     board_Display.endGame();
        //     board_Display.notifyObservers();
        // }
        // cout << "------4" << endl;
        // if(board_Display.inCheckmate(Colour:: WHITE)){
        //     board_Display.getBlackPlayer()->score++;
        //     board_Display.endGame();
        //     board_Display.notifyObservers();
        // }
        // cout << "------5" << endl;
        // if(board_Display.inCheckmate(Colour:: BLACK)){
        //     board_Display.getWhitePlayer()->score++;
        //     board_Display.endGame();
        //     board_Display.notifyObservers();
        // }

        // //ignore if no pawn promotion is happening
        // char pawnProm;
        // cin >> pawnProm;
        cout << "move cmd end" << endl;
    }
    else if (command == "setup") {
        board_Display.setUpGame();
    }
  }
}

