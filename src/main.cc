#include <iostream>
#include <vector>
#include<string>
#include<memory>

// #include "boarddisplay.h"
using namespace std;

int main () {

//     BoardDisplay board_Display;

//     string command;
//     while (cin >> command) {
//     if (command == "game" ) {
//         string playerOne, playerTwo;
//         cin >> playerOne >> playerTwo;
//         board_Display.addWhitePlayer(playerOne);
//         board_Display.addBlackPlayer(playerTwo);
//     }
//     else if (command == "resign") {
//         BoardDisplay::PlayerInfo* currentPlayer= board_Display.getCurrentPlayer();
//         board_Display.resign(currentPlayer->colour);
//     }
//     else if (command == "move") {
//         string oldPos, newPos;
//         cin >> oldPos >> newPos;
//         BoardDisplay::PlayerInfo* currentPlayer= board_Display.getCurrentPlayer();
//         board_Display.makeMove(currentPlayer-> colour, oldPos, newPos);
//         if(currentPlayer-> colour == WHITE ){
//             board_Display.inCheck(board_Display.getBlackPlayer()->colour);
//         }
//         if(currentPlayer-> colour == BLACK ){
//             board_Display.inCheck(board_Display.getWhitePlayer()->colour);
//         }
//         if(board_Display.inStalemate(Colour:: WHITE) || board_Display.inStalemate(Colour:: BLACK)){
//             //update score
//             //endgame
//             board_Display.getWhitePlayer()->score += 0.5;
//             board_Display.getBlackPlayer()->score += 0.5;
//             board_Display.endGame();
//             board_Display.notifyObservers();
//         }
//         if(board_Display.inCheckmate(Colour:: WHITE)){
//             board_Display.getBlackPlayer()->score++;
//             board_Display.endGame();
//             board_Display.notifyObservers();
//         }
//         if(board_Display.inCheckmate(Colour:: BLACK)){
//             board_Display.getWhitePlayer()->score++;
//             board_Display.endGame();
//             board_Display.notifyObservers();
//         }

//         //ignore if no pawn promotion is happening
//         char pawnProm;
//         cin >> pawnProm;

//     }
//     else if (command == "setup") {
//         board_Display.setUpGame();
//     }
//   }
}
