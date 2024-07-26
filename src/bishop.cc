#include "bishop.h"
#include "piece.h"

Bishop::Bishop(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
}

bool Bishop::isValidMove(char newC, int newI) {
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8){ //out of bounds 
        return false;
   }
    //make sure we're moving diagonally
    if (abs(newC - cPos) != abs(newI - iPos) && (newC != cPos && newI != iPos)) {
        return false;
    }

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