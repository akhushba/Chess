#include "pawn.h"

Pawn::Pawn(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos, 1)  {
    setPos(cPos, iPos);
}

bool Pawn::enpassent() {
    
}

bool Pawn::isValidMove(char newC, int newI) {
    if(newC < 'a' || newC> 'h' || newI < 1 || newI > 8){ 
        return false;
    }
    int direction = (colour == Colour::WHITE) ? 1 : -1;

    if(newI - iPos > 2*direction || newI - iPos <= 0) return false;
    else if(newI - iPos == 2*direction) {
        if(firstMove && newC == cPos) return true;
        else return false;
    } else if (newI - iPos == direction) {
        if(newC != cPos && board->capture(newC, newI)) return true;
        else if(newC == cPos && !(board->occupied(newC, newI))) return true;
        else return false;
    }
    return false;
}

void Pawn::generateMoves() {
    validPosVec.clear();
    int boardPosition = (colour == Colour::WHITE) ? 1 : -1;

    if (firstMove) {
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