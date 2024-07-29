#include <iostream>
#include <vector>
#include<string>
#include<memory>

#include "boarddisplay.h"
using namespace std;
#include "piece.h"

int main () {

    BoardDisplay board_Display;
    board_Display.defaultBoard();
    Piece* p  = board_Display.getBoardInfo('b', 2);
    cout << board_Display.checkValid(p, 'e', 2) << endl;

    //  cout << p->isValidMove('a', 3) << endl;
    // cout << p->getType() << p->getPosition().first << p->getPosition().second << endl;
}

