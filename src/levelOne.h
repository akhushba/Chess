#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"
class LevelOne : public Computer {
    public:
        LevelOne(string name, vector<Piece*> pieceSet, Colour c);
        pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) override;
        ~LevelOne() override = default;
};

#endif
