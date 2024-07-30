#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"

class BoardDisplay;

class Queen : public Piece {
public:
    Queen(Colour colour, char cPos, int iPos);
    ~Queen() override = default;
    vector <pair<char,int>> generate() override;

};

#endif

