#include "queen.h"
#include<iostream>

Queen::Queen(Colour colour, char cPos, int iPos): Piece(colour, 'q', cPos, iPos, 9) {
}

vector <pair<char,int>>Queen::generate(){
    vector <pair<char,int>> possible;
    //can move up, down, left, right, and in any diagonal direction
    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    //can move in any number of squares
    for (auto& direction : directions) {
        char col = cPos;
        int row = iPos;

        while (row >= 1 && row <= 8 && col >= 'a' && col < 'h') {
            row += direction[0];
            col += direction[1];
            if(col < 'a' || col > 'h' || row < 1 || row > 8) break;
            possible.emplace_back(make_pair(col, row));
        }
    }
    return possible;

}

