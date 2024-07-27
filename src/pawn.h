#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    bool firstMove = false;

public: 
    Pawn(Colour colour, Chessboard *board, char cPos, int iPos);
    ~Pawn() = default;

    bool enpassent();
    bool isValidMove(char newC, int newI) override;
    void generateMoves() override;
};

#endif