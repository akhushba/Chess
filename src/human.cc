#include "player.h"
#include "human.h"
#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

Human::Human(string name, vector<Piece*> pieceSet, Colour c) : Player(name, pieceSet, c) {};

pair<Piece*, pair<char, int>> Human::move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) {
    
}
