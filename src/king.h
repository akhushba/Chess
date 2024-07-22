#ifndef _KING_H_
#define _KING_H_

#include "piece.h"

class King : public Piece {
    bool canCastle();
public:
    King(Colour colour, char type, Chessboard *board, char cPos, int iPos);
    bool isValidMove(char newC, int newI);
    ~King();
};
#endif
