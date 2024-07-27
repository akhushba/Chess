#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"
#include "player.h"

class LevelOne : public Computer {
public:
    LevelOne(string name, vector<Piece*> pieceSet);
    void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
    ~LevelOne() override {}
};

#endif
