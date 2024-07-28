#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece{
    public: 
        Knight(Colour colour, Chessboard *board, char cPos, int iPos);
        ~Knight() override = default;

        bool isValidMove(char newC, int newI) override;
        void generateMoves() override;
};

#endif