#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"

class LevelOne : public Computer {
public:
    LevelOne();
    void move() override;
    ~LevelOne() override;
};

#endif