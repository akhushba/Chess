#ifndef PIECE_H
#define PIECE_H
#include <string>

using namespace std;

class Board;

class Piece{
protected:
    tuple<char, int> position();
    void captures(Piece *p);
    tuple<int, int> getCoordinate(char c, int i);

    bool Active;
    Board *board;
    char Type;
public:
    ~Piece();
    Piece();
    Piece(enum colour, char type, Board *board);

    bool isValidMove(char c, int i);
    enum Colour{WHITE,BLACK};
};

#endif