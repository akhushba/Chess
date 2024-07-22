#include "bishop.h"

Bishop::Bishop(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {

}

bool Bishop::isValidMove(char newC, int newI) {
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
        
        if (board->occupied(currentCol, currentRow)) {
            return false; 
        }
    }

    return true;
}