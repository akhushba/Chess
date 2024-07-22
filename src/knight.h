#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece{
public: 
Knight(Colour colour, char type, Chessboard *board, char cPos, int iPos);
~Knight();

bool isValidMove(char newC, int newI);
};

#endif