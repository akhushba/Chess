#include "levelThree.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

using namespace std; 

LevelThree::LevelThree(string name, vector<Piece*> pieceSet) : Computer(name, pieceSet) {}

void LevelThree::move(Piece* p = nullptr, char c = '\0', int i = -1) {
    if(p != nullptr && c != '\0' && i != -1) throw CustomException("An error occured while trying call move function on computer instead of human");
    // choose random piece and valid position
    // iterate through the list of the opponents pieces
    // call isValidMove on each opponent piece given randomly chosen position
    // continue iterating until we find a piece for which isValidMove returns false for each one of the opponents pieces

    int numPieces = pieceSet.size();
    char newC;
    int newI;
    bool goodMove;

    random_device rd;
    mt19937 g(rd());

    // randomly shuffle the pieceSet vector
    shuffle(pieceSet.begin(), pieceSet.end(), g);

    for (int i = 0; i < numPieces; i++) {
        // randomly shuffle the validPosVec vector
        shuffle(pieceSet[i]->validPosVec.begin(), pieceSet[i]->validPosVec.end(), g);

        for (int j = 0; j < pieceSet[i]->validPosVec.size(); j++) {

            // possible valid position that a piece can move to
            newC = get<0>(pieceSet[i]->validPosVec[j]);
            newI = get<1>(pieceSet[i]->validPosVec[j]);
            // reset bool each time
            goodMove = true;

            // iterate through the vector of the opponents pieces
            for (int k = 0; k < pieceSet[i]->getOpponent()->pieceSet.size(); k++) {
                // check first that the position in question is a valid capture move
                if (pieceSet[i]->capture(newC, newI) != nullptr) {
                    // temporarily set this captured opponent piece to inactive
                    pieceSet[i]->capture(newC, newI)->setActiveStatus(false);
                    // we need to check that this position can not be moved to by any of the opponent's players
                    if (pieceSet[i]->getOpponent()->pieceSet[k]->isValidMove(newC, newI) == true) {
                        goodMove = false;
                        break;
                    }
                    // set captured opponent back to active
                    pieceSet[i]->capture(newC, newI)->setActiveStatus(true);
                // if no pieces can be captured, just move somewhere where we are safe
                } else {
                    if (pieceSet[i]->getOpponent()->pieceSet[k]->isValidMove(newC, newI) == true) {
                        goodMove = false;
                        break;
                    }
                }
            }

            if (goodMove) {
                pieceSet[i]->setPos(newC, newI);
                return;
            }
        }
    }

    // if there is no safe move, then just choose a random valid move
    char newC = std::get<0>(pieceSet.at(0)->validPosVec.at(0));
    int newI = std::get<1>(pieceSet.at(0)->validPosVec.at(0));
    pieceSet[0]->setPos(newC, newI);
}
