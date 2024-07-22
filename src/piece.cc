#include "piece.h"
#include <iostream>
#include <tuple>

using namespace std;

Piece::Piece(Colour colour, char type, Chessboard *board, char cPos, int iPos) : colour {colour}, type{type}, board{board}, cPos{cPos}, iPos{iPos} {
    active = true;
}

void Piece::setPos(char c, int i) {
    cPos = c;
    iPos = i;
}
