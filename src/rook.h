#ifndef ROOK_H
#define ROOK_H

#include <utility>
#include<iostream>

#include "piece.h"

class Rook : public Piece{
    public: 
        Rook(Colour colour, char cPos, int iPos);
        ~Rook() override= default;

        vector<pair<char,int>> generate() override;
};

#endif
