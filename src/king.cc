#include "king.h"

King::King(Colour colour, BoardDisplay*board, char cPos, int iPos) : Piece(colour, 'k', board, iPos, cPos, 10) {
}

bool King::isValidMove(char newC, int newI) {
    //bound checking
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8) return false;
    int direction = (colour == Colour::WHITE) ? 1 : -1;
    //can't stay put
    if(newC == cPos && newI == iPos) return false;
    //can only castle in certain conditions
    else if (abs(newC - cPos) == 2 && newI == iPos && !boardInfo->canCastle(colour)) return false;
    //can only move a differnce of 1 from its origianl position
    else if(abs(newC - cPos) != 1 && abs(newI - iPos) != 1) return false;
    //cant move to position occupied by its own colour
    else if (boardInfo->occupied(newC, newI) == colour) return false;
    
    if(boardInfo->simulateAttack(this, newC, newI)) return false;
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