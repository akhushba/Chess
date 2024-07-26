#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelFour : public Computer {
public:
    LevelFour();
    void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
    ~LevelFour() override;
};

#endif