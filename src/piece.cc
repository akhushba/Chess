#include "piece.h"
#include <iostream>
#include <tuple>

using namespace std;
Piece::~Piece() {}

Piece::Piece(Colour colour, char type, char cPos, int iPos, int pieceValue) 
    : colour{colour}, type{colour == BLACK ? type : static_cast<char>(type - 32)}, cPos{cPos}, iPos{iPos}, pieceValue{pieceValue} {
}

void Piece::setPos(char c, int i) {
    cPos = c;
    iPos = i;
}

Piece* Piece::capture(char c, int i) {
    return this;
}

int Piece::getPieceValue() {
    return pieceValue;
}

vector<pair<char,int>> Piece::generate(){
    return {};
}
