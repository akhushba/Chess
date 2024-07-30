#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

#include "levelTwo.h"

using namespace std;

LevelTwo::LevelTwo(string name, vector<Piece*> pieceSet, Colour c) : Computer(name, pieceSet, c) {}

pair<Piece*, pair<char, int>> LevelTwo::move(vector<pair<Piece*, vector<pair<char, int>>>>) {
    // if(p != nullptr && c != '\0' && i != -1) throw CustomException("An error occured while trying call move function on computer instead of human");
    // int numPieces = pieceSet.size();
    // char newC;
    // int newI;

    // random_device rd;
    // mt19937 g(rd());

    // // randomly shuffle the pieceSet vector
    // shuffle(pieceSet.begin(), pieceSet.end(), g);

    // for (int i = 0; i < numPieces; i++) {
    //     // randomly shuffle the validPosVec vector
    //     shuffle(pieceSet.at(i)->validPosVec.begin(), pieceSet.at(i)->validPosVec.end(), g);

    //     for (int j = 0; j < pieceSet.at(i)->validPosVec.size(); j++) {
    //         newC = get<0>(pieceSet.at(i)->validPosVec[j]);
    //         newI = get<1>(pieceSet.at(i)->validPosVec[j]);
    //         if (board->canCapture(pieceSet.at(i)->getColour(), newC, newI)) {
    //             board->setState(pieceSet.at(i), newC, newI);
    //             return;
    //         }
    //     }
    // }
    
    // // if we have reached this point, there are no moves that can capture another piece
    // // so we can just use index 0 to choose a random move since the vectors are already shuffled/randomized
    // char potentialC = get<0>(pieceSet.at(0)->validPosVec.at(0));
    // int potentialI = get<1>(pieceSet.at(0)->validPosVec.at(0));
    // board->setState(pieceSet.at(0), potentialC, potentialI);
    // // pieceSet[0]->setPos(newC, newI);
}
