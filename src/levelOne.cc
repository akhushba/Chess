#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

#include "levelOne.h"

using namespace std;

LevelOne::LevelOne(string name, vector<Piece*> pieceSet, Colour c) : Computer(name, pieceSet, c) {}

pair<Piece*, pair<char, int>> LevelOne::move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves) {
    // if(p != nullptr && c != '\0' && i != -1) throw CustomException("An error occured while trying call move function on computer instead of human");

    char newC;
    int newI;

    random_device rd;
    mt19937 g(rd());

    // randomly shuffle the pieceSet vector
    shuffle(pieceAndMoves.begin(), pieceAndMoves.end(), g);
    // randomly shuffle the validPosVec vector
    shuffle(get<1>(pieceAndMoves[0]).begin(), get<1>(pieceAndMoves[0]).end(), g);

    cout << pieceAndMoves.size() << ", " << get<1>(pieceAndMoves[0]).size() << endl;
    newC = get<0>(get<1>(pieceAndMoves[0])[0]);
    newI = get<1>(get<1>(pieceAndMoves[0])[0]);
    cout << "hi" << endl;
    return make_pair(get<0>(pieceAndMoves[0]), make_pair(newC, newI));

    // board->setState(get<0>(pieceAndMoves[0]), newC, newI);

    // pieceSet.at(0)->setPos(newC, newI);
}
