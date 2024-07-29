#include <iostream>
#include <vector>
#include<string>
#include<memory>

#include "boarddisplay.h"
using namespace std;
#include "piece.h"

int main () {

    BoardDisplay board_Display;
    board_Display.addPiece('R', "a1");
    board_Display.addPiece('R', "a6");
    board_Display.notifyObservers();
    Piece* p  = board_Display.getBoardInfo('a', 1);
    cout << p->getType() << p->getPosition().first << p->getPosition().second << endl;

    cout << board_Display.checkValid(p, 'a', 6) << endl;

    //  cout << p->isValidMove('a', 3) << endl;
}

