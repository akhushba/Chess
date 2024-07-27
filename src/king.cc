#include "king.h"

King::King(Colour colour, char type, Chessboard*board, char cPos, int iPos) : Piece(colour, type, board, iPos, cPos, 10) {
}

bool King::canCastle() {
    if(!firstMove) return false;

}

bool King::isValidMove(char newC, int newI) {
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8){ //out of bounds 
        return false;
   }
    if(newC == cPos && newI == iPos) return false;
    if(abs(newC - cPos) != 1 && abs(newI - iPos) != 1) return false;

    if (board->capture(newC, newI)) {
        return true; 
    } else if (board->occupied(newC, newI)) {
        return false; 
    }
    
    return true;
}

void King::generateMoves() {
    validPosVec.clear();

    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(auto& d : directions) {
        if(isValidMove(cPos + d[0], iPos + d[1])) 
            validPosVec.emplace_back(make_tuple(cPos + d[0], iPos + d[1]));
    }
}