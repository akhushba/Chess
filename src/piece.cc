#include "piece.h"
#include <iostream>
#include <tuple>

using namespace std;

Piece::Piece(Colour colour, char type, BoardDisplay *board, char cPos, int iPos, int pieceValue) 
    : colour{colour}, boardInfo{boardInfo}, cPos{cPos}, iPos{iPos}, pieceValue{pieceValue}, 
      type{colour == BLACK ? type : static_cast<char>(type - 32)} {
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
        return boardInfo->getBlackPlayer()->player.get();
    } else if (colour == BLACK) {
        return boardInfo->getWhitePlayer()->player.get();
    }
}

int Piece::getPieceValue() {
    return pieceValue;
}
