#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

class Player {
protected:
    string name;
public:
    vector<Piece*> pieceSet; 
    Player() {}
    Player(string name, vector<Piece*> pieceSet) : name{name}, pieceSet{pieceSet} {}
    virtual void move(Piece* p , char c, int i) = 0;
    virtual void move() = 0;
    virtual ~Player() {}
};

#endif
