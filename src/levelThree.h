#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelThree : public Computer {
public:
    LevelThree();
    void move() override;
    ~LevelThree() override;
};

#endif