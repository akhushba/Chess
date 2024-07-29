#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

#include "levelOne.h"

using namespace std;

LevelOne::LevelOne(string name, vector<Piece*> pieceSet) : Computer(name, pieceSet) {}

void LevelOne::move(Piece* p, char c, int i) {
    if(p != nullptr && c != '\0' && i != -1) throw CustomException("An error occured while trying call move function on computer instead of human");

    int numPieces = pieceSet.size();
    char newC;
    int newI;

    random_device rd;
    mt19937 g(rd());

    // randomly shuffle the pieceSet vector
    shuffle(pieceSet.begin(), pieceSet.end(), g);
    // randomly shuffle the validPosVec vector
    shuffle(pieceSet.at(0)->validPosVec.begin(), pieceSet.at(0)->validPosVec.end(), g);

    newC = get<0>(pieceSet.at(0)->validPosVec.at(0));
    newI = get<1>(pieceSet.at(0)->validPosVec.at(0));
    board->setState(pieceSet.at(0), newC, newI);
    // pieceSet.at(0)->setPos(newC, newI);
}
