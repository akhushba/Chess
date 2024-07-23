#include "chessboard.h"

bool Chessboard::capture(char c, int i){
    return false;
}

bool Chessboard::occupied(char c, int i){
    return false;
}

Player* Chessboard::getWhitePlayer() {
    return WhitePlayer;
}

Player* Chessboard::getBlackPlayer() {
    return BlackPlayer;
}
