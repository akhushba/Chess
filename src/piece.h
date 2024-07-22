#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "colour.h"

using namespace std;

class Board;

class Piece{
protected:
    void captures(Piece *p);
    tuple<char, int> getCoordinate(char c, int i);

    bool active;
    Board *board;
    Colour colour;
    char type;

    char cPos;
    int iPos;
public:
    ~Piece();
    Piece(Colour colour, char type, Board *board, char cPos, int iPos);

    bool isValidMove(char c, int i);
    void setPos(char c, int i);
};

#endif