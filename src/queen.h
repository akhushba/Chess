#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"

class Queen : public Piece {
    public:
        Queen(Colour colour, Chessboard *board, char cPos, int iPos);
        bool isValidMove(char newC, int newI) override;
        void generateMoves() override;
        ~Queen() = default;
};
#endif
