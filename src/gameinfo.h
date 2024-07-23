#ifndef GAMEINFO_H
#define GAMEINFO_H
#include <string>
#include "colour.h"
#include "player.h"
#include "piece.h"
#include <vector>

using namespace std;

class GameInfo{
    public: 
        vector<Piece *> whitePieces;
        vector<Piece *> blackPieces;
        Player* turn;
};

#endif