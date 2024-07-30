#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"

class BoardDisplay;

class Bishop : public Piece {
    public:
        Bishop(Colour colour, BoardDisplay *board, char cPos, int iPos);
        bool isValidMove(char newC, int newI) override;
        void generateMoves() override;
        ~Bishop() override = default;
        vector <pair<char,int>> generate() override;
};
#endif
