#include "king.h"

King::King(Colour colour, char type, Chessboard*board, char cPos, int iPos) : Piece(colour, type, board, iPos, cPos) {
    Piece::setPos(cPos, iPos);
}

bool King::isValidMove(char newC, int newI) {
    
}

bool King::canCastle() {
    
}
