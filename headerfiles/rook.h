#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece{
public: 
Rook();
virtual ~Rook() = default;

bool isValidMove(char newC, int newI);
};

#endif