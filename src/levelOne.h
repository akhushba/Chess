#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"
class LevelOne : public Computer {
    public:
        LevelOne(string name, vector<Piece*> *pieceSet, Colour c);
        void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
        ~LevelOne() override = default;
};

#endif
