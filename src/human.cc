#include "human.h"
#include <iostream>

using namespace std;

Human::Human(string name, vector<Piece*> pieceSet) : Player{name, pieceSet} {}

void Human::move(Piece* p, int x, int y) {
    
}

Human::~Human() {}