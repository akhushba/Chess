#ifndef LEVELONE_H
#define LEVELONE_H

#include "computer.h"
class LevelThree : public Computer {
    public:
        LevelThree(string name, vector<Piece*> pieceSet);
        void move(Piece* p = nullptr, char c = '\0', int i = -1) override;
        ~LevelThree() override;
};

#endif