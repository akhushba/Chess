#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"

class BoardDisplay;

class Bishop : public Piece {
    public:
        Bishop(Colour colour, char cPos, int iPos);
        ~Bishop() override = default;
        vector <pair<char,int>> generate() override;
};
#endif
