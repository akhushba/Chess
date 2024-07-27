#include "boarddisplay.h"

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

char BoardDisplay::getState(int row, int col) const {
    //figure out
}

BoardDisplay::~BoardDisplay() {
    for(int i = 0; i < 8; i++) {
        delete[] board[i];
    }
}