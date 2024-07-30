#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {

    public: 
        Pawn(Colour colour, char cPos, int iPos);
        ~Pawn() override = default;

        vector <pair<char,int>> generate() override;

};

#endif