#ifndef _KING_H_
#define _KING_H_

#include "piece.h"

class King : Public Piece {
    bool canCastle();
public:
    King();
    bool isValidMove(<char newC, int newI>);
    virtual ~King() = default;
};
#endif
