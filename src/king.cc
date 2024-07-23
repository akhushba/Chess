#include "king.h"

King::King(Colour colour, char type, Chessboard*board, char cPos, int iPos) : Piece(colour, type, board, iPos, cPos) {
}

bool King::canCastle() {
    if(!firstMove) return false;

}

bool King::isValidMove(char newC, int newI) {
    if(newC == cPos && newI == iPos) return false;
    if(abs(newC - cPos) != 1 && abs(newI - iPos) != 1) return false;

    if (board->capture(newC, newI)) {
        return true; 
    } else if (board->occupied(newC, newI)) {
        return false; 
    }
    
    return true;
}
