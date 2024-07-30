#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece{
    public: 
        Knight(Colour colour, char cPos, int iPos);
        ~Knight() override = default;

        vector <pair<char,int>> generate() override;

};

#endif
