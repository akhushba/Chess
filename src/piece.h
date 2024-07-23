#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "colour.h"
#include "chessboard.h"

using namespace std;

class Piece{
protected:
    tuple<char, int> getCoordinate(char c, int i);

    bool active;
    Chessboard *board;
    Colour colour;
    char type;

    char cPos;
    int iPos;
public:
    Piece(Colour colour, char type, Chessboard *board, char cPos, int iPos);

    vector<tuple<char, int>> validPosVec;
    virtual bool isValidMove(char c, int i) = 0;
    virtual void generateMoves() = 0;
    void setPos(char c, int i);
    void setActiveStatus(bool newStatus);
    Piece* captures(char c, int i);

    ~Piece();
};

#endif