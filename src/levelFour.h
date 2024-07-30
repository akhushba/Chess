#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "computer.h"

class LevelFour : public Computer {
public:
    LevelFour(string name, vector<Piece*> pieceSet, Colour c);
    pair<Piece*, pair<char, int>> move(vector<pair<Piece*, vector<pair<char, int>>>>) override;
    int getMaxPieceValue(vector<pair<Piece*, tuple<char, int>>>);
    ~LevelFour() override = default;
};

#endif