#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

#include "levelThree.h"

using namespace std; 

LevelThree::LevelThree(string name, vector<Piece*> pieceSet, Colour c) : Computer(name, pieceSet, c) {}

pair<Piece*, pair<char, int>> LevelThree::move(vector<pair<Piece*, vector<pair<char, int>>>>) {
    // if(p != nullptr && c != '\0' && i != -1) throw CustomException("An error occured while trying call move function on computer instead of human");
    // // choose random piece and valid position
    // // iterate through the list of the opponents pieces
    // // call isValidMove on each opponent piece given randomly chosen position
    // // continue iterating until we find a piece for which isValidMove returns false for each one of the opponents pieces

    // int numPieces = pieceSet.size();
    // char newC;
    // int newI;
    // bool goodMove;

    // random_device rd;
    // mt19937 g(rd());

    // // randomly shuffle the pieceSet vector
    // shuffle(pieceSet.begin(), pieceSet.end(), g);

    // for (int i = 0; i < numPieces; i++) {
    //     // randomly shuffle the validPosVec vector
    //     shuffle(pieceSet.at(i)->validPosVec.begin(), pieceSet.at(i)->validPosVec.end(), g);
        
    //     for (int j = 0; j < pieceSet.at(i)->validPosVec.size(); j++) {

    //         // possible valid position that a piece can move to
    //         newC = get<0>(pieceSet.at(i)->validPosVec.at(j));
    //         newI = get<1>(pieceSet.at(i)->validPosVec.at(j));
    //         // reset bool each time
    //         goodMove = true;

    //         // iterate through the vector of the opponents pieces
    //         for (int k = 0; k < pieceSet.at(i)->getOpponent()->pieceSet.size(); k++) {
    //             // check first that the position in question is a valid capture move
    //             if (pieceSet.at(i)->capture(newC, newI) != nullptr) {
    //                 // temporarily set this captured opponent piece to inactive
    //                 pieceSet.at(i)->capture(newC, newI)->setActiveStatus(false);
    //                 // we need to check that this position can not be moved to by any of the opponent's players
    //                 if (pieceSet.at(i)->getOpponent()->pieceSet.at(k)->isValidMove(newC, newI) == true) {
    //                     goodMove = false;
    //                     break;
    //                 }
    //                 // set captured opponent back to active
    //                 pieceSet.at(i)->capture(newC, newI)->setActiveStatus(true);
    //             // if no pieces can be captured, just move somewhere where we are safe
    //             } else {
    //                 if (pieceSet.at(i)->getOpponent()->pieceSet.at(k)->isValidMove(newC, newI) == true) {
    //                     goodMove = false;
    //                     break;
    //                 }
    //             }
    //         }

    //         if (goodMove) {
    //             board->setState(pieceSet.at(i), newC, newI);
    //             // pieceSet.at(i)->setPos(newC, newI);
    //             return;
    //         }
    //     }
    // }

    // // if there is no safe move, then just choose a random valid move
    // char potentialC = get<0>(pieceSet.at(0)->validPosVec.at(0));
    // int potentialI = get<1>(pieceSet.at(0)->validPosVec.at(0));
    // board->setState(pieceSet.at(0), potentialC, potentialI);
    // // pieceSet.at(0)->setPos(newC, newI);
}
