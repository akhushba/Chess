#include "bishop.h"

Bishop::Bishop(Colour colour, char type, Board *board, char cPos, int iPos): Piece(colour, type, board), Piece::position{<cPos, iPos>} {

}

bool Bishop::isValidMove(char newC, int newI) {

}