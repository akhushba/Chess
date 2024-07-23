#include "piece.h"
#include <iostream>
#include <tuple>

using namespace std;

Piece::Piece(Colour colour, char type, Chessboard *board, char cPos, int iPos) : colour {colour}, type{type}, board{board}, cPos{cPos}, iPos{iPos} {
    active = true;
}

void Piece::setPos(char c, int i) {
    if (capture(c, i) != nullptr) {
        capture(c, i)->active = false;
    }
    cPos = c;
    iPos = i;
}

void Piece::setActiveStatus(bool newStatus) {
    active = newStatus;
}

Player* Piece::getOpponent() {
    if (colour == WHITE) {
        return board->getBlackPlayer();
    } else if (colour == BLACK) {
        return board->getWhitePlayer();
    }
}
