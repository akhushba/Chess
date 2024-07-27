#include "levelFour.h"
#include <algorithm>

using namespace std;

LevelFour::LevelFour(string name, vector<Piece*> pieceSet) : Computer(name, pieceSet) {}

void LevelFour::move(Piece* p = nullptr, char c = '\0', int i = -1) {
    // prioritize avoiding being captured
    // prioritize being in one of the 4 middle squares
    // prioritize capturing
    // otherwise random valid move

    // maybe: check for pawn first move

    int numPieces = pieceSet.size();
    bool canMoveMiddle = false;

    for (int i = 0; i < numPieces; i++) {
        if (find(pieceSet[i]->validPosVec.begin(), pieceSet[i]->validPosVec.end(), make_tuple('e', 4)) != pieceSet[i]->validPosVec.end()) {
            canMoveMiddle = true;
        } else if (find(pieceSet[i]->validPosVec.begin(), pieceSet[i]->validPosVec.end(), make_tuple('d', 4)) != pieceSet[i]->validPosVec.end()) {

        } else if (find(pieceSet[i]->validPosVec.begin(), pieceSet[i]->validPosVec.end(), make_tuple('e', 5)) != pieceSet[i]->validPosVec.end()) {

        } else if (find(pieceSet[i]->validPosVec.begin(), pieceSet[i]->validPosVec.end(), make_tuple('d', 4)) != pieceSet[i]->validPosVec.end()) {

        }
    }
}