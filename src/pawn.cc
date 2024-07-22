#include "pawn.h"

Pawn::Pawn(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
    setPos(cPos, iPos);
}

bool Pawn::enpassent() {
    
}

bool Pawn::isValidMove(char newC, int newI) {
    if(newI - iPos > 2 || newI - iPos <= 0) return false;
    if(newI - iPos == 2) {
        if(abs(newC - cPos) != 1) return false;
        else if(board->captures(newC, newI)) return true;
        else return false;
    }
    else if (newI - iPos == 1) {
        if(newC != cPos) return false;
        else if(board->captures(newC, newI)) return false;
        else return true;
    }
    return false;
}

void generateMoves() {
    // validPosVec.clear();
    // validPosVec.push_back(make_tuple('a', 1));
}

Pawn::~Pawn() {
    
}