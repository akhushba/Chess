#include "knight.h"

Knight::Knight(Colour colour, BoardDisplay *board, char cPos, int iPos): Piece(colour, 'n', board, cPos, iPos, 3)  {
}

bool Knight::isValidMove(char newC, int newI) {
    //bound checking
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8) return false;

    if(newC == cPos && newI == iPos){
        return false;
    }
    
    //move in an l shape, 1 position moves 2 spaces, the other moves 1
    if (abs(newC - cPos) == 2 && abs(newI - iPos) != 1) return false;
    else if (abs(newI - iPos) == 2 && abs(newC - cPos) != 1) return false;
    // can't move to a square occupied by your own colour
    else if (boardInfo->occupied(newC, newI) == colour) return false;

    //avoid being in check logic, simulateAttack returns true if King is in check
    if(boardInfo->simulateAttack(this, newC, newI)) return false;
    return true;
}

void Knight::generateMoves() {
    validPosVec.clear();

    int directions[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

    for(auto& d : directions) {
        if(isValidMove(cPos + d[0], iPos + d[1])) 
            validPosVec.emplace_back(make_tuple(cPos + d[0], iPos + d[1]));
    }
}

vector <pair<char,int>> Knight::generate() {
    vector <pair<char,int>> possible;
    int directions[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

    for(auto& d : directions) {
       if(cPos + d[0] < 'a' || cPos + d[0] > 'h' || iPos + d[1] < 1 || iPos + d[1] > 8) continue;
            possible.emplace_back(make_pair(cPos + d[0], iPos + d[1]));
    }
    return possible;
}
