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
void BoardDisplay::setState(char cPos, int iPos, Piece* p) {
    //figure out
    board[iPos - 1][cPos - 'a']->piece = p;

    char type = p->getType();
    PlayerInfo* currentPlayer = p->getColour() == BLACK ? blackPlayer : whitePlayer;

    if(type == 'k' || type == 'K') currentPlayer->kingPosition = {cPos, iPos};
}

char BoardDisplay::getState(int row, int col) const {
    //figure out
}

bool BoardDisplay::simulateInCheck(Piece* p, char newC, int newI) {
    pair<char, int> currentPosition = p->getPosition();

    Piece* tempCapture = board[newI - 1][newC - 'a']->piece;
    setState(newI, newC, p);
    setState(currentPosition.second, currentPosition.first, nullptr);

    PlayerInfo* oppositePlayer = p->getColour() == BLACK ? blackPlayer : whitePlayer;
    PlayerInfo* currentPlayer = p->getColour() == BLACK ? blackPlayer : whitePlayer;

    bool canCheck = false;

    for(const auto& piece : oppositePlayer->pieces) {
        canCheck = piece->isValidMove(currentPlayer->kingPosition.first, currentPlayer->kingPosition.second);
    }
    
    setState(newI, newC, tempCapture);
    setState(currentPosition.second, currentPosition.first, p);

    return canCheck;
}

BoardDisplay::~BoardDisplay() {
    for(int i = 0; i < 8; i++) {
        delete[] board[i];
    }
}