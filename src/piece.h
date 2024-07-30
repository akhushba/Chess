#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include "colour.h"
#include "boarddisplay.h"

class Player;

class Piece {
protected:

    const Colour colour;
    const char type;

    char cPos;
    int iPos;
    const int pieceValue;

public:
    bool hasMoved = false;

    Piece(Colour colour, char type, char cPos, int iPos, int pieceValue);

    void setPos(char c, int i);
    Piece* capture(char c, int i);
    int getPieceValue();

    std::pair<char, int> getPosition() const { return {cPos, iPos}; }
    Colour getColour() const { return colour; }
    char getType() const { return type; }
    virtual vector <pair<char,int>> generate() = 0;
    virtual ~Piece() = 0;
};

#endif // PIECE_H