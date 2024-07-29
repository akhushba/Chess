#include "levelFour.h"

#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <random>

using namespace std;

LevelFour::LevelFour(string name, vector<Piece*> pieceSet) : Computer(name, pieceSet) {}

// returns which move option captures the most valuable piece
int LevelFour::getMaxPieceValue(vector<pair<Piece*, tuple<char, int>>> optionsVec) {
    if (optionsVec.empty()) return -1;

    int maxIndex = 0;
    int maxValue = optionsVec[0].first->getPieceValue();
    char charPos = get<0>(optionsVec[0].second);
    int intPos = get<1>(optionsVec[0].second);

    for (int i = 1; i < optionsVec.size(); ++i) {
        int currentValue = optionsVec[i].first->capture(charPos, intPos)->getPieceValue();
        if (currentValue > maxValue) {
            maxValue = currentValue;
            maxIndex = i;
        }
    }

    return maxIndex;
}

void LevelFour::move(Piece* p = nullptr, char c = '\0', int i = -1) {
    // maybe: check for popular pawn first move
    // maybe: be ok w having pawn captured if capturing smth of higher value

    vector<pair<Piece*, tuple<char, int>>> safeOptions;
    vector<pair<Piece*, tuple<char, int>>> captureOptions;
    vector<pair<Piece*, tuple<char, int>>> centerOptions;
    
    unordered_set<pair<Piece*, tuple<char, int>>> commonElements;
    vector<pair<Piece*, tuple<char, int>>> safeCaptureAndCenter;
    vector<pair<Piece*, tuple<char, int>>> safeAndCapture;

    int numPieces = pieceSet.size();
    bool canMoveMiddle = false;
    bool goodMove, canAttack;
    char newC;
    int newI;
    int index;

    random_device rd;
    mt19937 g(rd());

    for (int i = 0; i < numPieces; i++) {
        for (int j = 0; j < pieceSet[i]->validPosVec.size(); j++) {
            newC = get<0>(pieceSet[i]->validPosVec[j]);
            newI = get<1>(pieceSet[i]->validPosVec[j]);

            if ((newC == 'e' || newC == 'd') && (newI == 4 || newI == 5)) {
                centerOptions.push_back(make_pair(pieceSet[i], make_tuple(newC, newI)));
            }

            if (pieceSet[i]->capture(newC, newI) != nullptr) {
                // check if moving "my" piece puts any of my other pieces in danger (but only for those that are higher value)
                for (int k = 0; i < numPieces; i++) {
                    if (pieceSet[k]->getPieceValue() > pieceSet[i]->getPieceValue()) {
                        canAttack = callSimulateAttack(pieceSet[i], newC, newI, pieceSet[k]);
                        if (canAttack == true) break;
                    }
                }
                if (canAttack == false) {
                    captureOptions.push_back(make_pair(pieceSet[i], make_tuple(newC, newI)));
                }
            }
            goodMove = true;
            for (int k = 0; k < pieceSet[i]->getOpponent()->pieceSet.size(); k++) {
                if (pieceSet[i]->getOpponent()->pieceSet[k]->isValidMove(newC, newI) == true) {
                    goodMove = false;
                    break;
                }
            }
            if (goodMove) {
                centerOptions.push_back(make_pair(pieceSet[i], make_tuple(newC, newI)));
            }
        }
    }
    // set common elems to vec1
    for (const auto& elem : safeOptions) {
        commonElements.insert(elem);
    }
    // find common elems in vec1 and vec2
    safeCaptureAndCenter.clear();
    for (const auto& elem : centerOptions) {
        if (commonElements.find(elem) != commonElements.end()) {
            safeCaptureAndCenter.push_back(elem);
            safeAndCapture.push_back(elem);
        }
    }
    // reset common elems to be the common elems between vec1 and vec2
    commonElements.clear();
    for (const auto& elem : safeCaptureAndCenter) {
        commonElements.insert(elem);
    }
    // find common elems between all 3 vecs
    safeCaptureAndCenter.clear();
    for (const auto& elem : captureOptions) {
        if (commonElements.find(elem) != commonElements.end()) {
            safeCaptureAndCenter.push_back(elem);
        }
    }

    if (safeCaptureAndCenter.size() == 0 && safeAndCapture.size() == 0) {
        // no overlap in any of the vectors
        shuffle(pieceSet.begin(), pieceSet.end(), g);
        newC = get<0>(get<1>(safeOptions[0]));
        newI = get<1>(get<1>(safeOptions[0]));
        pieceSet[0]->setPos(newC, newI);
    } else if (safeCaptureAndCenter.size() == 0) {
        // smth exists in 2 of the vectors
        index = getMaxPieceValue(safeAndCapture);
        newC = get<0>(get<1>(safeAndCapture[index]));
        newI = get<1>(get<1>(safeAndCapture[index]));
        pieceSet[index]->setPos(newC, newI);
        pieceSet[index]->capture(newC, newI)->setActiveStatus(false);
    } else {
        // there is smth that exists in all 3 vectors
        index = getMaxPieceValue(safeCaptureAndCenter);
        newC = get<0>(get<1>(safeCaptureAndCenter[index]));
        newI = get<1>(get<1>(safeCaptureAndCenter[index]));
        pieceSet[index]->setPos(newC, newI);
        pieceSet[index]->capture(newC, newI)->setActiveStatus(false);
    }
}