#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "colour.h"
#include "chessboard.h"

using namespace std;

class Piece{
protected:
    void captures(Piece *p);
    tuple<char, int> getCoordinate(char c, int i);

    bool active;
    Chessboard *board;
    Colour colour;
    char type;

    char cPos;
    int iPos;
public:
    ~Piece();
    Piece(Colour colour, char type, Chessboard *board, char cPos, int iPos);

    virtual bool isValidMove(char c, int i);
    void setPos(char c, int i);
};

#endif