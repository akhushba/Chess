#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player {
protected:
    int level;
public:
    Computer(int level);
    virtual void move() override = 0;
    virtual ~Computer() = 0;
};

#endif