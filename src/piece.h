#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <vector>
#include <tuple>
#include "colour.h"
#include "chessboard.h"

using namespace std;

class Piece{
protected:
    tuple<char, int> getCoordinate(char c, int i);

    bool active;
    Chessboard *board;
    const Colour colour;
    const char type;

    char cPos;
    int iPos;
    const int pieceValue;
    
public:
    Piece(Colour colour, char type, Chessboard *board, char cPos, int iPos, int pieceValue);

    vector<tuple<char, int>> validPosVec;
    virtual bool isValidMove(char c, int i) = 0;
    virtual void generateMoves() = 0;
    void setPos(char c, int i);
    void setActiveStatus(bool newStatus);
    Piece* capture(char c, int i);
    Player* getOpponent();
    int getPieceValue();

    virtual ~Piece();
};

#endif