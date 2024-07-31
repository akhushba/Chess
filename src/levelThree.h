#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "computer.h"
class LevelThree : public Computer {
    public:
        LevelThree(string name, Colour c);
        pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) override;
        ~LevelThree() override = default;
};

#endif
