#ifndef PIECE_H
#define PIECE_H
#include <string>
#include "colour.h"

using namespace std;

class Board;

class Piece{
protected:
    tuple<char, int> position;
    void captures(Piece *p);
    tuple<char, int> getCoordinate(char c, int i);

    bool Active;
    Board *board;
    char type;
    Colour colour;
public:
    ~Piece();
    Piece(Colour colour, char type, Board *board);

    bool isValidMove(char c, int i);
    void setPos(char c, int i);
};

#endif