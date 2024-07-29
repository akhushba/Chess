#include "queen.h"

Queen::Queen(Colour colour, BoardDisplay *board, char cPos, int iPos): Piece(colour, 'q', board, cPos, iPos, 9) {
    Piece::setPos(cPos, iPos);
}

bool Queen::isValidMove(char newC, int newI) {
    // Boundary checking
    if (newC < 'a' || newC > 'h' || newI < 1 || newI > 8) return false;

    // Check if not moving
    if (newC == cPos && newI == iPos) return false;
    // Final position must not have a piece of the same colour
    if (boardInfo->occupied(newC, newI) == colour) return false;

    // Determine movement direction
    int colDiff = newC - cPos;
    int rowDiff = newI - iPos;
    int colStep = (colDiff == 0) ? 0 : (colDiff > 0) ? 1 : -1;
    int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0) ? 1 : -1;

    // Check if move is along a valid path for a Queen
    if ((colDiff != 0 && rowDiff != 0 && abs(colDiff) != abs(rowDiff)) || (colDiff == 0 && rowDiff == 0)) return false;

    //make sure all squares inbetween are unoccupied
    char currentCol = cPos;
    int currentRow = iPos;
    while (currentCol != newC && currentRow != newI) {
        currentCol += colStep;
        currentRow += rowStep;
        
        if (boardInfo->occupied(currentCol, currentRow) == colour) return false;
    }

    // Ensure the move doesn't put the player's king in check
    if (boardInfo->simulateAttack(this, newC, newI)) return false;

    return true;
}


void Queen::generateMoves() {
    validPosVec.clear();

    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

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