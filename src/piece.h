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
    std::tuple<char, int> getCoordinate(char c, int i);

    bool active;
    BoardDisplay *boardInfo;
    const Colour colour;
    const char type;

    char cPos;
    int iPos;
    const int pieceValue;

public:
    bool hasMoved = false;
    std::vector<std::tuple<char, int>> validPosVec;

    Piece(Colour colour, char type, BoardDisplay *board, char cPos, int iPos, int pieceValue);

    virtual bool isValidMove(char c, int i) = 0;
    virtual void generateMoves() = 0;
    void setPos(char c, int i);
    void setActiveStatus(bool state);
    Player* getOpponent();
    int getPieceValue();

    std::pair<char, int> getPosition() const { return {cPos, iPos}; }
    Colour getColour() const { return colour; }
    char getType() const { return type; }

    virtual ~Piece() = 0;
};

#endif // PIECE_H