#ifndef LEVELTHREE_H
#define LEVELTHREE_H

#include "computer.h"
class LevelThree : public Computer {
    public:
        LevelThree(string name, vector<Piece*> *pieceSet, Colour c);
        void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
        ~LevelThree() override = default;
};

#endif