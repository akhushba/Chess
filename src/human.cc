#include "player.h"
#include "human.h"
#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

Human::Human(string name, Colour c) : Player(name, c) {};

pair<Piece*, pair<char, int>> Human::move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) {
    char newC = (pieceAndMoves[0].second)[0].first;
    int newI = (pieceAndMoves[0].second)[0].second;
    
    return make_pair(pieceAndMoves[0].first, make_pair(newC, newI));
}
