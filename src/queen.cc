#include "queen.h"

Queen::Queen(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos) {
    Piece::setPos(cPos, iPos);
}

bool Queen::isValidMove(char newC, int newI) {
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
            
            if (board->captures(currentCol, currentRow)) {
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
            
            if (board->captures(currentCol, currentRow)) {
                return true; 
            } else if (board->occupied(currentCol, currentRow)) {
                return false; 
            }
        }
    }
    else return false;

    return true;
}