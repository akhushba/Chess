#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <string>
#include "colour.h"
#include "player.h"
#include "piece.h"
#include "gameinfo.h"
#include <vector>

using namespace std;


class Chessboard{
    Player*** board;
    Player* WhitePlayer;
    Player* BlackPlayer;

    vector<vector<Piece *>> board;
    bool gameOver;
    int whiteScore;
    int blackScore;
    void initBoard();

    public: 
        bool inStalemate();
        bool inCheckmate();
        bool inCheck();
        Colour occupied(char c, int i);
        void resign();
        void takeInput();
        Player* getWhitePlayer();
        Player* getBlackPlayer();
};

#endif