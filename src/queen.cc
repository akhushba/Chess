#include "queen.h"

Queen::Queen(Colour colour, char type, Board *board, char cPos, int iPos): Piece(colour, type, board) {
    Piece::setPos(cPos, iPos);
}

bool Queen::isValidMove(char newC, int newI) {

}