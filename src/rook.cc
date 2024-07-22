#include "rook.h"
#include <cstdlib>

Rook::Rook(Colour colour, char type, Chessboard *board, char cPos, int iPos) : Piece(colour, type, board, cPos, iPos) {
}

bool Rook::isValidMove(char newC, int newI) {
    //make sure we're moving horizontally or vertically
    if ((newC != cPos && newI != iPos) || (newC == cPos && newI == iPos)) {
        return false;
    }

    int colStep = (newC == cPos)? 0 : (newC > cPos) ? 1 : -1;
    int rowStep = (newC == cPos)? 0 : (newI > iPos) ? 1 : -1;

    char currentCol = cPos;
    int currentRow = iPos;

    while (currentCol != newC && currentRow != newI) {
        currentCol += colStep;
        currentRow += rowStep;
        
        if (board->occupied(currentCol, currentRow)) {
            return false; 
        }
    }

    return true;
}

vector<tuple<int, int>> generateMves() {
     // keep i pos the same and go through a-h for cpos and call is valid move
    //keep cpos the same and go though 1-8 for ipos and call is calid move
}