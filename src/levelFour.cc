#include "levelFour.h"

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <random>

using namespace std;

LevelFour::LevelFour(string name, vector<Piece*> *pieceSet, Colour c) : Computer(name, pieceSet, c) {}

// returns which move option captures the most valuable piece
int LevelFour::getMaxPieceValue(vector<pair<Piece*, tuple<char, int>>> optionsVec) {
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

void LevelFour::move(Piece* p, char c, int i) {
    vector<pair<Piece*, tuple<char, int>>> safeOptions;
    vector<pair<Piece*, tuple<char, int>>> captureOptions;
    vector<pair<Piece*, tuple<char, int>>> centerOptions;
    
    vector<pair<Piece*, tuple<char, int>>> safeCaptureAndCenter;
    vector<pair<Piece*, tuple<char, int>>> safeAndCapture;

    int numPieces = pieceSet->size();
    bool canMoveMiddle = false;
    bool goodMove, canAttack;
    char newC;
    int newI;
    int index;

    random_device rd;
    mt19937 g(rd());

    for (int i = 0; i < numPieces; i++) {
        for (int j = 0; j < pieceSet->at(i)->validPosVec.size(); j++) {
            newC = get<0>(pieceSet->at(i)->validPosVec.at(j));
            newI = get<1>(pieceSet->at(i)->validPosVec.at(j));

            if ((newC == 'e' || newC == 'd') && (newI == 4 || newI == 5)) {
                centerOptions.push_back(make_pair(pieceSet->at(i), make_tuple(newC, newI)));
            }

            if (pieceSet->at(i)->capture(newC, newI) != nullptr) {
                canAttack = false;
                for (int k = 0; k < numPieces; k++) {
                    if (pieceSet->at(k)->getPieceValue() > pieceSet->at(i)->getPieceValue()) {
                        canAttack = callSimulateAttack(pieceSet->at(i), newC, newI, pieceSet->at(k));
                        if (canAttack) break;
                    }
                }
                if (!canAttack) {
                    captureOptions.push_back(make_pair(pieceSet->at(i), make_tuple(newC, newI)));
                }
            }

            goodMove = true;
            for (int k = 0; k < pieceSet->at(i)->getOpponent()->pieceSet->size(); k++) {
                if (pieceSet->at(i)->getOpponent()->pieceSet->at(k)->isValidMove(newC, newI)) {
                    goodMove = false;
                    break;
                }
            }
            if (goodMove) {
                safeOptions.push_back(make_pair(pieceSet->at(i), make_tuple(newC, newI)));
            }
        }
    }

    // Find common elements in safeOptions and captureOptions
    for (const auto& safeOption : safeOptions) {
        for (const auto& captureOption : captureOptions) {
            if (safeOption == captureOption) {
                safeAndCapture.push_back(safeOption);
            }
        }
    }

    // Find common elements in safeAndCapture and centerOptions
    for (const auto& safeCapture : safeAndCapture) {
        for (const auto& centerOption : centerOptions) {
            if (safeCapture == centerOption) {
                safeCaptureAndCenter.push_back(safeCapture);
            }
        }
    }

    if (safeOptions.empty()) {
        // No safe options, make a random move
        shuffle(pieceSet->begin(), pieceSet->end(), g);
        char newC = std::get<0>(pieceSet->at(0)->validPosVec.at(0));
        int newI = std::get<1>(pieceSet->at(0)->validPosVec.at(0));
        board->setState(pieceSet->at(0), newC, newI);
    } else if (safeCaptureAndCenter.empty() && safeAndCapture.empty()) {
        // No overlap in any of the vectors
        shuffle(pieceSet->begin(), pieceSet->end(), g);
        newC = get<0>(get<1>(safeOptions.at(0)));
        newI = get<1>(get<1>(safeOptions.at(0)));
        board->setState(pieceSet->at(0), newC, newI);
    } else if (safeCaptureAndCenter.empty()) {
        // Something exists in 2 of the vectors
        index = getMaxPieceValue(safeAndCapture);
        newC = get<0>(get<1>(safeAndCapture.at(index)));
        newI = get<1>(get<1>(safeAndCapture.at(index)));
        board->setState(pieceSet->at(index), newC, newI);
        pieceSet->at(index)->capture(newC, newI)->setActiveStatus(false);
    } else {
        // There is something that exists in all 3 vectors
        index = getMaxPieceValue(safeCaptureAndCenter);
        newC = get<0>(get<1>(safeCaptureAndCenter.at(index)));
        newI = get<1>(get<1>(safeCaptureAndCenter.at(index)));
        board->setState(pieceSet->at(index), newC, newI);
        pieceSet->at(index)->capture(newC, newI)->setActiveStatus(false);
    }
}
