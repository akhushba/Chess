#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelTwo : public Computer {
public:
    LevelTwo(string name, vector<Piece*> pieceSet);
    void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
    ~LevelTwo() override;
};

#endif