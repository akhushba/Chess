#include "pawn.h"

Pawn::Pawn(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
    setPos(cPos, iPos);
}

bool Pawn::enpassent() {
    
}

bool Pawn::isValidMove(char newC, int newI) {
    int direction = (colour == Colour::WHITE) ? 1 : -1;
    if(newI - iPos > 2*direction || newI - iPos <= 0) return false;
    if(newI - iPos == 2*direction) {
        if(abs(newC - cPos) != 1) return false;
        else if(board->captures(newC, newI)) return true;
        else return false;
    }
    else if (newI - iPos == direction) {
        if(newC != cPos) return false;
        else if(board->captures(newC, newI)) return false;
        else return true;
    }
    return false;
}

void Pawn::generateMoves() {
    validPosVec.clear();
    int direction = (colour == Colour::WHITE) ? 1 : -1;
    char nextC = cPos;
    int nextI = iPos + direction;
    if (isValidMove(nextC, nextI)) {
        validPosVec.emplace_back(nextC, nextI);
    }
    if (firstMove) {
        nextI = iPos + 2 * direction;
        if (isValidMove(nextC, nextI)) {
            validPosVec.emplace_back(nextC, nextI);
        }
    }
    char diagC = cPos;
    int diagI = iPos + direction;
    if (isValidMove(diagC + 1, diagI)) {
        validPosVec.emplace_back(diagC + 1, diagI);
    }
    if (isValidMove(diagC - 1, diagI)) {
        validPosVec.emplace_back(diagC - 1, diagI);
    }
}

Pawn::~Pawn() {
    
}
