#include "bishop.h"

Bishop::Bishop(Colour colour, BoardDisplay *board, char cPos, int iPos): Piece(colour, 'b', board, cPos, iPos, 3)  {
}

bool Bishop::isValidMove(char newC, int newI) {
    //bound checking
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8) return false;

    //can't stay in the same place
    if (newC == cPos && newI == iPos) return false;
    //make sure we're moving diagonally
    if (abs(newC - cPos) != abs(newI - iPos) && newC != cPos && newI != iPos)
        return false;
    // Final position must not have a piece of the same colour
    if (boardInfo->occupied(newC, newI) == colour) return false;

    int colStep = (newC > cPos) ? 1 : -1;
    int rowStep = (newI > iPos) ? 1 : -1;

    //make sure all squares inbetween are unoccupied
    char currentCol = cPos;
    int currentRow = iPos;
    while (currentCol != newC && currentRow != newI) {
        currentCol += colStep;
        currentRow += rowStep;
        
        if (boardInfo->occupied(currentCol, currentRow) == colour) return false;
    }

    if(boardInfo->simulateAttack(this, newC, newI)) return false;
    return true;
}

void Bishop::generateMoves() {
    validPosVec.clear();
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

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