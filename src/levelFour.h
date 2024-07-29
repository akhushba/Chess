#ifndef LEVELFOUR_H
#define LEVELFOUR_H

#include "computer.h"

class LevelFour : public Computer {
public:
    LevelFour(string name, vector<Piece*> pieceSet);
    void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
    int getMaxPieceValue(vector<pair<Piece*, tuple<char, int>>>) override;
    ~LevelFour() override = default;
};

#endif