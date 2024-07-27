#include "knight.h"

Knight::Knight(Colour colour, Chessboard *board, char cPos, int iPos): Piece(colour, 'n', board, cPos, iPos, 3)  {
    setPos(cPos, iPos);
}

bool Knight::isValidMove(char newC, int newI) {
    if(newC == cPos && newI == iPos){
        return false;
    }
    //make sure that newc is either +- 2 or new i is +- 2
    if((abs(newC - cPos) != 2 && abs(newI - iPos) != 1 ) || abs(newC - cPos) != 1 && abs(newI - iPos) != 2 ){
        return false;
    }
   if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8){ //out of bounds 
        return false;
   }
    if (board->capture(newC, newI)) {
        return true; 
    } else if (board->occupied(newC, newI)) {
        return false; 
    }
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