#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"

class Computer : public Player {

public:
    Computer(string name, Colour c);
    virtual pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) override = 0;
    
    virtual ~Computer() override = 0;
};

#endif

