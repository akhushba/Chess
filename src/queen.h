#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"
#include "boarddisplay.h"

class Queen : public Piece {
public:
    Queen(Colour colour, BoardDisplay *board, char cPos, int iPos);
    bool isValidMove(char newC, int newI) override;  
    void generateMoves() override;
    ~Queen() override = default;
};

#endif
