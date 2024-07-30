#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "computer.h"
class LevelThree : public Computer {
    public:
        LevelThree(string name, vector<Piece*> pieceSet, Colour c);
        pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>>) override;
        ~LevelThree() override = default;
};

#endif