#include "pawn.h"

Pawn::Pawn(Colour colour, BoardDisplay *board, char cPos, int iPos): Piece(colour, 'p', board, cPos, iPos, 1)  {
    setPos(cPos, iPos);
}

bool Pawn::isValidMove(char newC, int newI) {
    //bound checking
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8) return false;

    int direction = (colour == Colour::WHITE) ? 1 : -1;

    //must move forward 1 or 2 spaces
    if(newI - iPos > 2*direction || newI - iPos <= 0) return false;
    //trying to move 2 spaces after first move
    else if(newI - iPos == 2*direction && !hasMoved) return false;
    //moving diagonally but can't capture
    else if (newC != cPos && (boardInfo->occupied(newC, newI) != colour || boardInfo->occupied(newC, newI) == NULL_C)) 
        return false;
    //moving forward blocked
    else if(newC == cPos && boardInfo->occupied(newC, newI) != NULL_C)
        return false;

    //avoid being in check logic, simulateAttack returns true if King is in check
    if(boardInfo->simulateAttack(this, newC, newI)) return false;
    return true;
}

void Pawn::generateMoves() {
    validPosVec.clear();
    int boardPosition = (colour == Colour::WHITE) ? 1 : -1;

    if (hasMoved) {
        if (isValidMove(cPos, iPos + 2 * boardPosition)) {
            validPosVec.emplace_back(cPos, iPos + 2 * boardPosition);
        }
    }

    int directions[4][2] = {{0, boardPosition}, {1, boardPosition}, {-1, boardPosition}};
    for(auto& d : directions) {
        if(isValidMove(cPos + d[0], iPos + d[1])) 
            validPosVec.emplace_back(make_tuple(cPos + d[0], iPos + d[1]));
    }
}