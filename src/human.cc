#include "player.h"
#include "human.h"
#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

Human::Human(string name, vector<Piece*> pieceSet, Colour c) : Player(name, pieceSet, c) {};

// this is will a single element vector for (Human)
pair<Piece*, pair<char, int>> Human::move(vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves, vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves, vector<pair<Piece*, vector<pair<char, int>>>> opponentPieceAndMoves) {
    

    // cout << "hi" << endl;
    // i don't even think we need this line anymore
    // if(p == nullptr && c == '\0' && i == -1) throw CustomException("An error occured while trying call move function on human instead of computer");
    
    // if (board->checkValid(p, c, i)) {
    //     board->setState(p, c, i);
    // }

    // if (p->isValidMove(c, i)) {
    //     board->setState(p, c, i);
    //     // p->setPos(c, i);
    // }
}