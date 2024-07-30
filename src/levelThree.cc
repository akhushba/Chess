#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

#include "levelThree.h"

using namespace std; 

LevelThree::LevelThree(string name, vector<Piece*> pieceSet, Colour c) : Computer(name, pieceSet, c) {}

pair<Piece*, pair<char, int>> LevelThree::move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) {
    int numPieces = pieceAndMoves.size();
    char newC;
    int newI;
    bool safeMove = true;

    random_device rd;
    mt19937 g(rd());

    // randomly shuffle the pieceSet vector
    shuffle(pieceAndMoves.begin(), pieceAndMoves.end(), g);
    shuffle(pieceAndCaptureMoves.begin(), pieceAndCaptureMoves.end(), g);

    // if capture and avoid capture
    for (auto& [piece1, moveSet1] : pieceAndMoves) {
        shuffle(moveSet1.begin(), moveSet1.end(), g);
        for (auto& [piece2, moveSet2] : pieceAndCaptureMoves) {
            if (piece1 == piece2) {
                for (const auto& move1 : moveSet1) {
                    for (const auto& move2 : moveSet2) {
                        if (move1 == move2) {
                            for (const auto& [opponentPiece, opponentMoves] : opponentPieceAndMoves) {
                                for (const auto& opponentMove : opponentMoves) {
                                    if (opponentMove == move1) {
                                        safeMove = false;
                                    }
                                }
                            }
                            if (safeMove) {return make_pair(piece1, move1);}
                        }
                    }
                }

            }
        }
    }

    for (const auto& [piece, moves] : pieceAndMoves) {
        for (const auto& move : moves) {
            bool moveExistsInOpponent = false;

            for (const auto& [opponentPiece, opponentMoves] : opponentPieceAndMoves) {
                if (find(opponentMoves.begin(), opponentMoves.end(), move) != opponentMoves.end()) {
                    moveExistsInOpponent = true;
                    break;
                }
            }
            if (!moveExistsInOpponent) {
                return make_pair(piece, move);
            }
        }
    }

    // if we have reached this point, there are no moves that can capture another piece
    // so we can just use index 0 to choose a random move since the vectors are already shuffled/randomized
    newC = get<0>(get<1>(pieceAndMoves[0])[0]);
    newI = get<1>(get<1>(pieceAndMoves[0])[0]);
    return make_pair(get<0>(pieceAndMoves[0]), make_pair(newC, newI));

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
