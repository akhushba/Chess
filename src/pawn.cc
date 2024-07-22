#include "pawn.h"

Pawn::Pawn(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
    setPos(cPos, iPos);
}

bool Pawn::isValidMove(char newC, int newI) {
    
}

bool Pawn::enpassent() {
    
}

Pawn::~Pawn() {
    
}