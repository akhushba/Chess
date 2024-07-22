#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece{
public: 

Pawn(Colour colour, char type, Chessboard *board, char cPos, int iPos);
~Pawn();

bool enpassent();
bool isValidMove(char newC, int newI);
};

#endif