#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelTwo : public Computer {
public:
    LevelTwo(string name, vector<Piece*> pieceSet);
    void move() override;
    ~LevelTwo() override;
};

#endif