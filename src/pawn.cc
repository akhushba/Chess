#include "pawn.h"
#include <utility>
#include<iostream>

Pawn::Pawn(Colour colour, char cPos, int iPos): Piece(colour, 'p', cPos, iPos, 1)  {
}


vector <pair<char,int>> Pawn::generate(){
    vector <pair<char,int>> possible;

    //only moves forward
    int boardPosition = (colour == Colour::WHITE) ? 1 : -1;

    //if it hasn't moved yet it can move two spaces straight
    if (!hasMoved) {
        if(!(cPos < 'a' || cPos > 'h' || iPos + 2 * boardPosition < 1 || iPos + 2 * boardPosition > 8))
        possible.emplace_back(make_pair(cPos, iPos + 2 * boardPosition));
    }
    //can potentially move one space forward diagonally or straight
    int directions[3][2] = {{0, boardPosition}, {1, boardPosition}, {-1, boardPosition}};
    for(auto& d : directions) {
        if(cPos + d[0] < 'a' || cPos + d[0] > 'h' || iPos + d[1] < 1 || iPos + d[1] > 8) continue;
        possible.emplace_back(make_pair(cPos + d[0], iPos + d[1]));
    }

    return possible;
}
