#include "queen.h"

Queen::Queen(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos) {
    Piece::setPos(cPos, iPos);
}

bool Queen::isValidMove(char newC, int newI) {
    
}