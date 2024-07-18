#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelTwo : public Computer {
public:
    LevelTwo();
    void move() override;
    ~LevelTwo() override;
};

#endif