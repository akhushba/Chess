#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
public: 

Pawn();
Pawn(Colour colour, Board *board);
~Pawn();

bool enpassent;
bool isValidMove(char newC, int newI);
};

#endif