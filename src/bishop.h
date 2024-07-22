#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"
#include "colour.h"
class Bishop : public Piece {
public:
    Bishop(Colour colour, char type, Chessboard *board, char cPos, int iPos);
    bool isValidMove(char newC, int newI);
    ~Bishop();
};
#endif
