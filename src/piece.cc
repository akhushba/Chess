#include "piece.h"
#include <iostream>
#include <tuple>

using namespace std;

Piece::Piece(Colour colour, char type, Board *board) : colour {colour}, type{type}, board{board} {}

void Piece::setPos(char c, int i) {
    position = make_tuple(c, i);
}
