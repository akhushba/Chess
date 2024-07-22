#include "human.h"
#include <iostream>
#include <tuple>

using namespace std;

Human::Human(string name, vector<Piece*> pieceSet) : Player{name, pieceSet} {}

void Human::move(Piece* p, char c, int i) {
    if (p->isValidMove(c, i)) {
        p->setPos(c, i);
    }
}

Human::~Human() {}