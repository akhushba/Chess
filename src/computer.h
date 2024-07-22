#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player {
public:
    Computer() : Player() {}
    virtual void move() override = 0;
    virtual ~Computer() override {};
};

#endif