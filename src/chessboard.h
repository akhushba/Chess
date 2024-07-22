#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <string>
#include "colour.h"
#include "player.h"
#include "piece.h"
#include <vector>

using namespace std;


class Chessboard{
    Player*** board;
    Player* WhitePlayer;
    Player* BlackPlayer;
    Player* turn;

    vector<vector<Piece *>> board;
    bool gameOver;
    int whiteScore;
    int blackScore;
    void initBoard();

    public: 
        bool inStalemate();
        bool inCheckmate();
        bool inCheck();
        bool captures(char c, int i);
        bool occupied(char c, int i);
        void resign();
        void takeInput();
};

#endif