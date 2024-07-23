#include "levelOne.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std;

LevelOne::LevelOne(string name, vector<Piece*> pieceSet) : Computer(name, pieceSet) {}

void LevelOne::move() {
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


    // int randPiece;
    // int numPieces = pieceSet.size();
    // int numValidPos;
    // int randPos;
    // char newC;
    // int newI;

    // srand(time(0));
    // randPiece = rand() % numPieces;

    // pieceSet[randPiece]->generateMoves();
    // numValidPos = pieceSet[randPiece]->validPosVec.size();
    
    // srand(time(0));
    // randPos = 1 + (rand() % numValidPos);
    // newC = get<0>(pieceSet[randPiece]->validPosVec[randPos]);
    // newI = get<1>(pieceSet[randPiece]->validPosVec[randPos]);

    // pieceSet[randPiece]->setPos(newC, newI);
}
