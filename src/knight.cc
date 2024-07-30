#include "knight.h"

Knight::Knight(Colour colour, char cPos, int iPos): Piece(colour, 'n', cPos, iPos, 3)  {
}

vector <pair<char,int>> Knight::generate() {
    vector <pair<char,int>> possible;
    int directions[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

    for(auto& d : directions) {
       if(cPos + d[0] < 'a' || cPos + d[0] > 'h' || iPos + d[1] < 1 || iPos + d[1] > 8) continue;
            possible.emplace_back(make_pair(cPos + d[0], iPos + d[1]));
    }
    return possible;
}
