#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <string>
#include "player.h"
#include "piece.h"
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
        void setCheck(bool inCheck, Colour c);
        Player* getWhitePlayer();
        Player* getBlackPlayer();
};

#endif