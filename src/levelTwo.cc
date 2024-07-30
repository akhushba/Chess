#include <iostream>
#include <random>
#include <algorithm>
#include <numeric>

#include "levelTwo.h"

using namespace std;

LevelTwo::LevelTwo(string name, vector<Piece*> pieceSet, Colour c) : Computer(name, pieceSet, c) {}

pair<Piece*, pair<char, int>> LevelTwo::move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves) {
    // if(p != nullptr && c != '\0' && i != -1) throw CustomException("An error occured while trying call move function on computer instead of human");
    int numPieces = pieceAndMoves.size();
    char newC;
    int newI;

    random_device rd;
    mt19937 g(rd());

    // randomly shuffle the pieceSet vector
    shuffle(pieceAndMoves.begin(), pieceAndMoves.end(), g);
    shuffle(pieceAndCaptureMoves.begin(), pieceAndCaptureMoves.end(), g);

    for (auto& [piece1, moves1] : pieceAndMoves) {
        shuffle(moves1.begin(), moves1.end(), g);
        for (auto& [piece2, moves2] : pieceAndCaptureMoves) {
            if (piece1 == piece2) {
                for (const auto& move1 : moves1) {
                    for (const auto& move2 : moves2) {
                        if (move1 == move2) {
                            return make_pair(piece1, move1);
                        }
                    }
                }
            }
        }
    }

    // if we have reached this point, there are no moves that can capture another piece
    // so we can just use index 0 to choose a random move since the vectors are already shuffled/randomized
    newC = get<0>(get<1>(pieceAndMoves[0])[0]);
    newI = get<1>(get<1>(pieceAndMoves[0])[0]);
    return make_pair(get<0>(pieceAndMoves[0]), make_pair(newC, newI));
}
