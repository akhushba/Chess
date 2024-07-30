#include "rook.h"
#include <cstdlib>

Rook::Rook(Colour colour, char cPos, int iPos) : Piece(colour, 'r', cPos, iPos, 5) {
}

vector <pair<char,int>> Rook::generate(){
    vector <pair<char,int>> possible;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for (auto& d : directions) {
        char col = cPos;
        int row = iPos;

        while (row >= 1 && row <= 8 && col >= 'a' && col <= 'h') {
            row += d[0];
            col += d[1];
            if(col < 'a' || col > 'h' || row < 1 || row > 8) break;
            // cout << col << row << endl;
            possible.emplace_back(make_pair(col, row));
        }
    }
    return possible;
}