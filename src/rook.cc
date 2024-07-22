#include "rook.h"

Rook::Rook(Colour colour, char type, Board *board, char cPos, int iPos) : Piece(colour, type, board) {
    Piece::setPos(cPos, iPos);
}

bool Rook::isValidMove(char newC, int newI) {
    if(get<0>(Piece::position) == newC || get<1>(Piece::position) == newI) 
        return false;
    else if {
        
    }
}

Rook::~Rook() {
    
}