#include "bishop.h"

Bishop::Bishop(Colour colour, char cPos, int iPos) : Piece(colour, 'b', cPos, iPos, 10) {
}

vector <pair<char,int>> Bishop::generate(){
    vector <pair<char,int>> possible;
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (auto& direction : directions) {
        char col = cPos;
        int row = iPos;

        while (row >= 1 && row <= 8 && col >= 'a' && col <= 'h') {
            row += direction[0];
            col += direction[1];
            if(col < 'a' || col > 'h' || row < 1 || row > 8) continue;
            possible.emplace_back(make_pair(col, row));
        }
    }
  return possible;
}
