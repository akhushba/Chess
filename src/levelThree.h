#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelThree : public Computer {
public:
    LevelThree(string name, vector<Piece*> pieceSet);
    void move() override;
    ~LevelThree() override;
};

#endif