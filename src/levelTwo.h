#ifndef LEVELTWO_H
#define LEVELTWO_H

#include "computer.h"

class LevelTwo : public Computer {
    public:
        LevelTwo(string name, vector<Piece*> pieceSet);
        void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
        ~LevelTwo() override = default;
};

#endif