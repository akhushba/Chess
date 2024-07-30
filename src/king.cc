#include "king.h"

King::King(Colour colour, char cPos, int iPos) : Piece(colour, 'k', cPos, iPos, 10) {
}

vector <pair<char,int>> King::generate(){
    vector <pair<char,int>> possible;
    int directions[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    for(auto& d : directions) {
        if(cPos + d[0] < 'a' || cPos + d[0] > 'h' || iPos + d[1] < 1 || iPos + d[1] > 8) continue;
            possible.emplace_back(make_pair(cPos + d[0], iPos + d[1]));
    }

    int casteIPos = colour == Colour::WHITE ? 1 : 8;
    possible.emplace_back(make_pair('g', casteIPos));
    return possible;
}

