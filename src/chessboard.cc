#include "chessboard.h"

Colour Chessboard::occupied(char c, int i){
    return BLACK;
}

Player* Chessboard::getWhitePlayer() {
    return WhitePlayer;
}

Player* Chessboard::getBlackPlayer() {
    return BlackPlayer;
}
