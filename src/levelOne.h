#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"
class LevelOne : public Computer {
    public:
        LevelOne(string name, vector<Piece*> pieceSet, Colour c);
        pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>>) override;
        ~LevelOne() override = default;
};

#endif
