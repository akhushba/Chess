#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
public:
    Human(string name, vector<Piece*> pieceSet);
    void move(Piece*p, int x, int y) override;
    ~Human();
};

#endif