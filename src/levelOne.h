#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"
#include "player.h"

class LevelOne : public Computer {
public:
    LevelOne(string name, vector<Piece*> pieceSet);
    void move() override;
    ~LevelOne() override {}
};

#endif
