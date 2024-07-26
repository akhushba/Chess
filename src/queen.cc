#include "queen.h"

Queen::Queen(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos) {
    Piece::setPos(cPos, iPos);
}

bool Queen::isValidMove(char newC, int newI) {
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8){ //out of bounds 
        return false;
   }
    //not in the same posiiton
    if(newC == cPos && newI == iPos) return false;

    //behave like a rook
    if(newC == cPos || newI == iPos) {
        int colStep = 0;
        int rowStep = 0;
        if(newC == cPos) rowStep = (newI > iPos) ? 1 : -1;
        else colStep = (newC > cPos) ? 1 : -1;

        char currentCol = cPos;
        int currentRow = iPos;

        while (currentCol != newC && currentRow != newI) {
            currentCol += colStep;
            currentRow += rowStep;
            
            if (board->capture(currentCol, currentRow)) {
                return true; 
            } else if (board->occupied(currentCol, currentRow)) {
                return false; 
            }
        }
    } 
    //behave like a bishop
    else if (abs(newC - cPos) == abs(newI - iPos)) {
        int colStep = (newC > cPos) ? 1 : -1;
        int rowStep = (newI > iPos) ? 1 : -1;

        char currentCol = cPos;
        int currentRow = iPos;

        while (currentCol != newC && currentRow != newI) {
            currentCol += colStep;
            currentRow += rowStep;
            
            if (board->capture(currentCol, currentRow)) {
                return true; 
            } else if (board->occupied(currentCol, currentRow)) {
                return false; 
            }
        }
    }
    else return false;

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