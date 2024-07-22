#include "levelOne.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

LevelOne::LevelOne(string name, vector<Piece*> pieceSet) : Computer(name, pieceSet) {}

void LevelOne::move() {
    int randPiece;
    int numPieces = pieceSet.size();
    int numValidPos;
    int randPos;
    char newC;
    int newI;

    srand(time(0));
    randPiece = 1 + (rand() % numPieces);

    pieceSet[randPiece]->generateMoves();
    numValidPos = pieceSet[randPiece]->validPosVec.size();
    
    srand(time(0));
    randPos = 1 + (rand() % numValidPos);
    newC = get<0>(pieceSet[randPiece]->validPosVec[randPos]);
    newI = get<1>(pieceSet[randPiece]->validPosVec[randPos]);

    pieceSet[randPiece]->setPos(newC, newI);
}
