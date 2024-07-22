#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop();
    bool isValidMove(char newC, int newI);
    virtual ~Bishop() = default;
};
#endif
