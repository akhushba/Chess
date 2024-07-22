#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"

class Queen : public Piece {
public:
    Queen(Colour colour, char type, Board *board, char cPos, int iPos);
    bool isValidMove(char newC, int newI);
    virtual ~Queen() = default;
};
#endif
