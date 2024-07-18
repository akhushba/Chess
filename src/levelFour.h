#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelFour : public Computer {
public:
    LevelFour();
    void move() override;
    ~LevelFour() override;
};

#endif