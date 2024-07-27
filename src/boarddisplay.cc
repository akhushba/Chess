#include "boarddisplay.h"
#include <utility>

void BoardDisplay::initializeBoard() {
    for(int i = 0; i < 8; i+=2) {
        for(int j = 0; j < 8; j+=2) {
            board[i][j] = new BoardSegment(WHITE);
            board[i][j+1] = new BoardSegment(BLACK);
            board[i+1][j] = new BoardSegment(BLACK);
            board[i+1][j+1] = new BoardSegment(WHITE);
        }
    }
}

void BoardDisplay::attach(Observer* o) {
    Subject::attach(o);
}

void BoardDisplay::detach(Observer* o) {
    Subject::detach(o);
}

void BoardDisplay::notifyObservers() {
    Subject::notifyObservers();
}

//character is the column, int is the row
void BoardDisplay::setState(Piece* p, char cPos, int iPos) {
    //figure out
    board[iPos - 1][cPos - 'a']->piece = p;

    char type = p->getType();
    PlayerInfo* currentPlayer = p->getColour() == BLACK ? blackPlayer : whitePlayer;

    if(type == 'k' || type == 'K') currentPlayer->kingPosition = {cPos, iPos};
}

char BoardDisplay::getState(int row, int col) const {
    
}

bool BoardDisplay::simulateInCheck(Piece* p, char newC, int newI) {
    pair<char, int> currentPosition = p->getPosition();

    Piece* tempCapture = board[newI - 1][newC - 'a']->piece;
    setState(p, newC, newI);
    setState(nullptr, currentPosition.first, currentPosition.second);

    PlayerInfo* oppositePlayer = p->getColour() == BLACK ? blackPlayer : whitePlayer;
    PlayerInfo* currentPlayer = p->getColour() == BLACK ? blackPlayer : whitePlayer;

    bool canCheck = false;

    for(const auto& piece : oppositePlayer->activePieces) {
        boardState->setCheck(false, currentPlayer->colour);
        canCheck = piece->isValidMove(currentPlayer->kingPosition.first, currentPlayer->kingPosition.second);
        boardState->setCheck(true, currentPlayer->colour);
    }
    
    setState(tempCapture, newC, newI);
    setState(p, currentPosition.first, currentPosition.second);

    return canCheck;
}

BoardDisplay::~BoardDisplay() {
    for(int i = 0; i < 8; i++) {
        delete[] board[i];
    }
}