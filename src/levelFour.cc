#include "levelFour.h"

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <random>

using namespace std;

LevelFour::LevelFour(string name, vector<Piece*> pieceSet, Colour c) : Computer(name, pieceSet, c) {}

// returns which move option captures the most valuable piece
int LevelFour::getMaxPieceValue(vector<pair<Piece*, pair<char, int>>> optionsVec) {
    if (optionsVec.empty()) return -1;

    int maxIndex = 0;
    int maxValue = optionsVec.at(0).first->getPieceValue();
    char charPos = get<0>(optionsVec.at(0).second);
    int intPos = get<1>(optionsVec.at(0).second);

    for (int i = 1; i < optionsVec.size(); ++i) {
        int currentValue = optionsVec.at(i).first->capture(charPos, intPos)->getPieceValue();
        if (currentValue > maxValue) {
            maxValue = currentValue;
            maxIndex = i;
        }
    }

    return maxIndex;
}

pair<Piece*, pair<char, int>> LevelFour::move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) {
    
    // find all moves in pieceAndMoves overlapping w pieceAndCaptureMoves not in opponentPieceAndMoves
    // find all moves in pieceAndMoves not in opponentPieceAndMoves
    // choose random move

    char newC;
    int newI;
    bool safeMove = true;
    int index;

    vector<pair<Piece*, pair<char, int>>> safeCaptureCenterOptions;
    vector<pair<Piece*, pair<char, int>>> safeCaptureOptions;
    vector<pair<Piece*, tuple<char, int>>> safeOptions;

    random_device rd;
    mt19937 g(rd());

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
                            // if occupies one of the center 4 squares
                            if ((move1.first == 'd' || move1.first == 'e') && (move1.second == '4' || move1.second == '5')) {
                                if (safeMove) {safeCaptureCenterOptions.emplace_back(make_pair(piece1, move1));}
                            } else {
                                if (safeMove) {safeCaptureOptions.emplace_back(make_pair(piece1, move1));}
                            }
                            
                        }
                    }
                }

            }
        }
    }

    // if just avoid capture
    for (const auto& [piece, moves] : pieceAndMoves) {
        for (const auto& move : moves) {
            bool moveExistsInOpponent = false;
            for (const auto& [opponentPiece, opponentMoves] : opponentPieceAndMoves) {
                if (find(opponentMoves.begin(), opponentMoves.end(), move) != opponentMoves.end()) {
                    moveExistsInOpponent = true;
                    break;
                }
            }
            if (!moveExistsInOpponent) safeOptions.emplace_back(make_pair(piece, move));
        }
    }

    // if we have reached this point, there are no moves that can capture another piece
    // so we can just use index 0 to choose a random move since the vectors are already shuffled/randomized
    newC = get<0>(get<1>(pieceAndMoves[0])[0]);
    newI = get<1>(get<1>(pieceAndMoves[0])[0]);
    return make_pair(get<0>(pieceAndMoves[0]), make_pair(newC, newI));

    if (safeOptions.empty()) {
        // No safe options, make a random move
        shuffle(pieceAndMoves.begin(), pieceAndMoves.end(), g);
        newC = (pieceAndMoves[0].second)[0].first;
        newI = (pieceAndMoves[0].second)[0].second;
        return make_pair(get<0>(pieceAndMoves[0]), make_pair(newC, newI));
    } else if (safeCaptureCenterOptions.empty() && safeCaptureCenterOptions.empty()) {
        // No overlap in any of the vectors
        shuffle(pieceAndMoves.begin(), pieceAndMoves.end(), g);
        newC = get<0>(get<1>(safeOptions[0]));
        newI = get<1>(get<1>(safeOptions[0]));
        return make_pair(get<0>(safeOptions[0]), make_pair(newC, newI));
    } else if (safeCaptureCenterOptions.empty()) {
        // Something exists in 2 of the vectors
        index = getMaxPieceValue(safeCaptureOptions);
        newC = get<0>(get<1>(safeCaptureOptions.at(index)));
        newI = get<1>(get<1>(safeCaptureOptions.at(index)));
        return make_pair(get<0>(safeCaptureOptions[index]), make_pair(newC, newI));
    } else {
        // There is something that exists in all 3 vectors
        index = getMaxPieceValue(safeCaptureCenterOptions);
        newC = get<0>(get<1>(safeCaptureCenterOptions[index]));
        newI = get<1>(get<1>(safeCaptureCenterOptions[index]));
        return make_pair(get<0>(safeCaptureCenterOptions[index]), make_pair(newC, newI));
    }



    // vector<pair<Piece*, tuple<char, int>>> safeOptions;
    // vector<pair<Piece*, tuple<char, int>>> captureOptions;
    // vector<pair<Piece*, tuple<char, int>>> centerOptions;
    
    // vector<pair<Piece*, tuple<char, int>>> safeCaptureAndCenter;
    // vector<pair<Piece*, tuple<char, int>>> safeAndCapture;

    // int numPieces = pieceSet.size();
    // bool canMoveMiddle = false;
    // bool goodMove, canAttack;
    // char newC;
    // int newI;
    // int index;

    // random_device rd;
    // mt19937 g(rd());

    // for (int i = 0; i < numPieces; i++) {
    //     for (int j = 0; j < pieceSet.at(i)->validPosVec.size(); j++) {
    //         newC = get<0>(pieceSet.at(i)->validPosVec.at(j));
    //         newI = get<1>(pieceSet.at(i)->validPosVec.at(j));

    //         if ((newC == 'e' || newC == 'd') && (newI == 4 || newI == 5)) {
    //             centerOptions.push_back(make_pair(pieceSet.at(i), make_tuple(newC, newI)));
    //         }

    //         if (pieceSet.at(i)->capture(newC, newI) != nullptr) {
    //             canAttack = false;
    //             for (int k = 0; k < numPieces; k++) {
    //                 if (pieceSet.at(k)->getPieceValue() > pieceSet.at(i)->getPieceValue()) {
    //                     canAttack = callSimulateAttack(pieceSet.at(i), newC, newI, pieceSet.at(k));
    //                     if (canAttack) break;
    //                 }
    //             }
    //             if (!canAttack) {
    //                 captureOptions.push_back(make_pair(pieceSet.at(i), make_tuple(newC, newI)));
    //             }
    //         }

    //         goodMove = true;
    //         for (int k = 0; k < pieceSet.at(i)->getOpponent()->pieceSet.size(); k++) {
    //             if (pieceSet.at(i)->getOpponent()->pieceSet.at(k)->isValidMove(newC, newI)) {
    //                 goodMove = false;
    //                 break;
    //             }
    //         }
    //         if (goodMove) {
    //             safeOptions.push_back(make_pair(pieceSet.at(i), make_tuple(newC, newI)));
    //         }
    //     }
    // }

    // // Find common elements in safeOptions and captureOptions
    // for (const auto& safeOption : safeOptions) {
    //     for (const auto& captureOption : captureOptions) {
    //         if (safeOption == captureOption) {
    //             safeAndCapture.push_back(safeOption);
    //         }
    //     }
    // }

    // // Find common elements in safeAndCapture and centerOptions
    // for (const auto& safeCapture : safeAndCapture) {
    //     for (const auto& centerOption : centerOptions) {
    //         if (safeCapture == centerOption) {
    //             safeCaptureAndCenter.push_back(safeCapture);
    //         }
    //     }
    // }

    // if (safeOptions.empty()) {
    //     // No safe options, make a random move
    //     shuffle(pieceSet.begin(), pieceSet.end(), g);
    //     char newC = std::get<0>(pieceSet.at(0)->validPosVec.at(0));
    //     int newI = std::get<1>(pieceSet.at(0)->validPosVec.at(0));
    //     board->setState(pieceSet.at(0), newC, newI);
    // } else if (safeCaptureAndCenter.empty() && safeAndCapture.empty()) {
    //     // No overlap in any of the vectors
    //     shuffle(pieceSet.begin(), pieceSet.end(), g);
    //     newC = get<0>(get<1>(safeOptions.at(0)));
    //     newI = get<1>(get<1>(safeOptions.at(0)));
    //     board->setState(pieceSet.at(0), newC, newI);
    // } else if (safeCaptureAndCenter.empty()) {
    //     // Something exists in 2 of the vectors
    //     index = getMaxPieceValue(safeAndCapture);
    //     newC = get<0>(get<1>(safeAndCapture.at(index)));
    //     newI = get<1>(get<1>(safeAndCapture.at(index)));
    //     board->setState(pieceSet.at(index), newC, newI);
    //     pieceSet.at(index)->capture(newC, newI)->setActiveStatus(false);
    // } else {
    //     // There is something that exists in all 3 vectors
    //     index = getMaxPieceValue(safeCaptureAndCenter);
    //     newC = get<0>(get<1>(safeCaptureAndCenter.at(index)));
    //     newI = get<1>(get<1>(safeCaptureAndCenter.at(index)));
    //     board->setState(pieceSet.at(index), newC, newI);
    //     pieceSet.at(index)->capture(newC, newI)->setActiveStatus(false);
    // }
}
