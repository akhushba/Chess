#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "computer.h"

class LevelFour : public Computer {
public:
    LevelFour(string name, Colour c);
    pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) override;
    int getMaxPieceValue(vector<pair<Piece*, pair<char, int>>>);
    ~LevelFour() override = default;
};

#endif
