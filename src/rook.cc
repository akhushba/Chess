#include "rook.h"
#include <cstdlib>

Rook::Rook(Colour colour, Chessboard *board, char cPos, int iPos) : Piece(colour, 'r', board, cPos, iPos, 5) {
}

bool Rook::isValidMove(char newC, int newI) {
    //bound checking
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8) return false;
    
    //can't stay in the same place
    if (newC == cPos && newI == iPos) return false;
    //make sure we're moving horizontally or vertically
    else if (newC != cPos && newI != iPos) return false;
    // Final position must not have a piece of the same colour
    if (board->occupied(newC, newI) == colour) return false;

    int colStep = (newC == cPos) ? 0 : (newC > cPos) ? 1 : -1;
    int rowStep = (newC == cPos) ? 0 : (newI > iPos) ? 1 : -1;

    //make sure all squares inbetween are unoccupied
    char currentCol = cPos;
    int currentRow = iPos;
    while (currentCol != newC && currentRow != newI) {
        currentCol += colStep;
        currentRow += rowStep;
        
        if (board->occupied(currentCol, currentRow) == colour) return false;
    }

    if(boardInfo->simulateInCheck(this, newC, newI)) return false;
    return true;
}

void Rook::generateMoves() {
    validPosVec.clear();

    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for (auto& direction : directions) {
        char col = cPos;
        int row = iPos;

        while (row >= 1 && row <= 8 && col >= 'a' && col < 'h') {
            row += direction[0];
            col += direction[1];
            if(isValidMove(col, row)) validPosVec.emplace_back(make_tuple(col, row));
        }
    }
}