#include "piece.h"
#include <iostream>
#include <tuple>

using namespace std;
Piece::~Piece() {}

Piece::Piece(Colour colour, char type, BoardDisplay *board, char cPos, int iPos, int pieceValue) 
    : colour{colour}, boardInfo{boardInfo}, cPos{cPos}, iPos{iPos}, pieceValue{pieceValue}, 
      type{colour == BLACK ? type : static_cast<char>(type - 32)} {
    active = true;
}

void Piece::setPos(char c, int i) {
    boardInfo->setState(this, c, i);
}

Piece* Piece::capture(char c, int i) {
    return this;
}

void Piece::setActiveStatus(bool state) {
    active = state;
}

Player* Piece::getOpponent() {
    return (colour == WHITE) ? boardInfo->getBlackPlayer()->player : boardInfo->getWhitePlayer()->player;
}

int Piece::getPieceValue() {
    return pieceValue;
}

vector<pair<char,int>> Piece::generate(){
    return {};
}

bool Piece::isValidMove(char c, int i) {}