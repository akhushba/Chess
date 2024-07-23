#include "levelTwo.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

LevelTwo::LevelTwo(string name, vector<Piece*> pieceSet) : Computer(name, pieceSet) {}

void LevelTwo::move() {
    int numPieces = pieceSet.size();
    char newC;
    int newI;

    random_device rd;
    mt19937 g(rd());

    // randomly shuffle the pieceSet vector
    shuffle(pieceSet.begin(), pieceSet.end(), g);

    for (int i = 0; i < numPieces; i++) {
        // randomly shuffle the validPosVec vector
        shuffle(pieceSet[i]->validPosVec.begin(), pieceSet[i]->validPosVec.end(), g);

        for (int j = 0; j < pieceSet[i]->validPosVec.size(); j++) {
            newC = get<0>(pieceSet[i]->validPosVec[j]);
            newI = get<1>(pieceSet[i]->validPosVec[j]);
            if (pieceSet[i]->captures(newC, newI) != nullptr) {
                pieceSet[i]->captures(newC, newI)->setActiveStatus(false);
                pieceSet[i]->setPos(newC, newI);
                return;
            }
        }
    }
    
    // we can just use index 0 since the vectors are already shuffled/randomized
    newC = get<0>(pieceSet[0]->validPosVec[0]);
    newI = get<1>(pieceSet[0]->validPosVec[0]);
    pieceSet[0]->setPos(newC, newI);
}
