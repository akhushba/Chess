#include "bishop.h"
#include "piece.h"

Bishop::Bishop(Colour colour, char type, Chessboard *board, char cPos, int iPos): Piece(colour, type, board, cPos, iPos)  {
    setPos(cPos, iPos);
}

bool Bishop::isValidMove(char newC, int newI) {

}

Bishop::~Bishop() {
    
}
