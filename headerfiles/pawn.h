#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
public: 

Pawn();
virtual ~Pawn() = default;

bool enpassent();
bool isValidMove(char newC, int newI);
};

#endif