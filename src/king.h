#ifndef _KING_H_
#define _KING_H_

#include "piece.h"
class BoardDisplay;

class King : public Piece {
    public:
        King(Colour colour, char cPos, int iPos);
        ~King() override = default;
        vector <pair<char,int>> generate() override;

};
#endif

