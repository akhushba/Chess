#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player {

public:
    Computer(string name, vector<Piece*> pieceSet);
    virtual void move(Piece* p = nullptr, char c = '\0', int i = -1) override = 0;
    
    virtual ~Computer() override = 0;
};

#endif
