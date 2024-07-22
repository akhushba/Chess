#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece{
public: 
Rook(Colour colour, char type, Board *board, char cPos, int iPos);
virtual ~Rook() = default;

bool isValidMove(char newC, int newI);
};

#endif