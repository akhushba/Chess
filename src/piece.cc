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
    boardInfo->setState(this, c, i);
}

void Piece::setActiveStatus(bool state) {
    active = state;
}

Player* Piece::getOpponent() {
    return (colour == WHITE) ? boardInfo->getBlackPlayer()->player.get() : boardInfo->getWhitePlayer()->player.get();
}

int Piece::getPieceValue() {
    return pieceValue;
}

bool Piece::isValidMove(char c, int i) {}