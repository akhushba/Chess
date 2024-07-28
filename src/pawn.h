#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {

    public: 
        Pawn(Colour colour, Chessboard *board, char cPos, int iPos);
        ~Pawn() override = default;

        bool isValidMove(char newC, int newI) override;
        void generateMoves() override;
};

#endif