#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "computer.h"

class LevelTwo : public Computer {
    public:
        LevelTwo(string name, vector<Piece*> pieceSet, Colour c);
        pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves) override;
        ~LevelTwo() override = default;
};

#endif