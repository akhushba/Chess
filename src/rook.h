#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece{
    public: 
        Rook(Colour colour, Chessboard *board, char cPos, int iPos);
        ~Rook() = default;

        bool isValidMove(char newC, int newI) override;
        void generateMoves() override;
};

#endif