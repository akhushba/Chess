#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelOne : public Computer {
public:
    LevelOne(string name, vector<Piece*> pieceSet) : Player(name, pieceSet) {}
    void move() override;
    ~LevelOne() override {};
};

#endif