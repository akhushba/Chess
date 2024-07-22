#include "king.h"

King::King(Colour colour, char type, Board *board, char cPos, int iPos) : Piece(colour, type, board) {
    Piece::setPos(cPos, iPos);
}

bool King::isValidMove(char newC, int newI) {
    
}

bool King::canCastle() {
    
}
