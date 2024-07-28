#include "levelOne.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

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
    shuffle(pieceSet[0]->validPosVec.begin(), pieceSet[0]->validPosVec.end(), g);

    newC = get<0>(pieceSet[0]->validPosVec[0]);
    newI = get<1>(pieceSet[0]->validPosVec[0]);
    pieceSet[0]->setPos(newC, newI);
}
