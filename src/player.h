#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "piece.h"
#include "boarddisplay.h"

using namespace std;

class BoardDisplay;
class Piece;

class Player {
protected:
    string name;
    Colour colour;
public:
    Player(string name, Colour c);
    string getName();
    
    virtual pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) = 0;
    virtual ~Player() = 0;
};

#endif

