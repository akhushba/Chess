#ifndef _KING_H_
#define _KING_H_

#include "piece.h"

class King : public Piece {
    bool canCastle();
    bool firstMove = false;
public:
    King(Colour colour, Chessboard *board, char cPos, int iPos);
    bool isValidMove(char newC, int newI) override;
    void generateMoves() override;
    ~King() = default;
};
#endif
