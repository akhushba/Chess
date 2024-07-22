#include "knight.h"

Knight::Knight(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
    setPos(cPos, iPos);
}

bool Knight::isValidMove(char newC, int newI) {
    
}

Knight::~Knight() {
    
}