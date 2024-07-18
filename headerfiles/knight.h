#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece{
public: 
Knight();
virtual ~Knight() = default;

bool isValidMove(char newC, int newI);
};

#endif