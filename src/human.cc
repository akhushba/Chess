#include "player.h"
#include "human.h"
#include <iostream>
#include <tuple>

using namespace std;

Human::Human(string name, vector<Piece*> pieceSet) : Player{name, pieceSet} {}

void Human::move(Piece* p, char c, int i) {
    if(p == nullptr && c == '\0' && i == -1) throw CustomException("An error occured while trying call move function on human instead of computer");
    if (p->isValidMove(c, i)) {
        board->setState(p, c, i);
        // p->setPos(c, i);
    }
}

Human::~Human() {}