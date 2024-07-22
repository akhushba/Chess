#include "piece.h"
#include <iostream>
#include <tuple>

using namespace std;

void Piece::setPos(char c, int i) {
    position = make_tuple(c, i);
}
