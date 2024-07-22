#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"

class Queen : public Piece {
public:
    Queen();
    bool isValidMove(char newC, int newI);
    virtual ~Queen() = default;
};
#endif
