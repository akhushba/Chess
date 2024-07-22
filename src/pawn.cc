#include "pawn.h"

Pawn::Pawn(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
    setPos(cPos, iPos);
}

bool Pawn::enpassent() {
    
}

bool Pawn::isValidMove(char newC, int newI) {
    if(newI - iPos > 2 || newI - iPos <= 0) return false;
    if(newI = iPos == 2) {
        if(newC != cPos) return false;
    }
}

