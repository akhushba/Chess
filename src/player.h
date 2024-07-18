#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "piece.h"

using namespace std;

class Player {
protected:
    string name;
    vector<Piece*> pieceSet; 
public:
    Player(string name, vector<Piece*> pieceSet) : name{name}, pieceSet{pieceSet} {};
    virtual void move(Piece* p , int x, int y);
    virtual void move();
    virtual ~Player() = 0;
};

#endif