#include "knight.h"

Knight::Knight(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
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
    if (board->captures(newC, newI)) {
        return true; 
    } else if (board->occupied(newC, newI)) {
        return false; 
    }
   return true;
}

vector<tuple<int, int>> generateMves() {
     // keep i pos the same and go through a-h for cpos and call is valid move
    //keep cpos the same and go though 1-8 for ipos and call is calid move
}