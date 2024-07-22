#include "rook.h"
#include <cstdlib>

Rook::Rook(Colour colour, char type, Board *board, char cPos, int iPos) : Piece(colour, type, board, cPos, iPos) {
}

bool Rook::isValidMove(char newC, int newI) {
    //make sure we're moving diagonally
    if (abs(newC - cPos) != abs(newI - iPos) && (newC - cPos)!=0 && (newI - iPos) != 0) {
        return false;
    }

    
}

Rook::~Rook() {
    
}