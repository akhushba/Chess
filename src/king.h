#ifndef _KING_H_
#define _KING_H_

#include "piece.h"

class King : public Piece {
    public:
        King(Colour colour, BoardDisplay *board, char cPos, int iPos);
        bool isValidMove(char newC, int newI) override;
        void generateMoves() override;
        ~King() override = default;
};
#endif
