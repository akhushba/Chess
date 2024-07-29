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
    board_Display.notifyObservers();
    Piece* p  = board_Display.getBoardInfo('a', 2);
    cout << board_Display.checkValid(p, 'a', 3) << endl;

    //  cout << p->isValidMove('a', 3) << endl;
}

