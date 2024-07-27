#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelFour : public Computer {
public:
    LevelFour(string name, vector<Piece*> pieceSet);
    void move() override;
    ~LevelFour() override;
};

#endif