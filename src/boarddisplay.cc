#include "boarddisplay.h"
#include <memory>

// Initialize the board with unique pointers to BoardSegment
void BoardDisplay::initializeBoard() {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            Colour segmentColor = ((i + j) % 2 == 0) ? WHITE : BLACK;
            board[i][j] = std::make_unique<BoardSegment>(segmentColor);
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

// Set the state of a board segment
void BoardDisplay::setState(Piece* p, char cPos, int iPos) {
    board[iPos - 1][cPos - 'a']->piece = p;

    char type = p->getType();
    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer.get() : whitePlayer.get();
    if(type == 'k' || type == 'K') {
        currentPlayer->kingPosition = {cPos, iPos};
    }
}

char BoardDisplay::getState(int row, int col) const {
    if (!board[row][col]->piece) {
        return board[row][col]->colour == BLACK ? '_' : ' ';
    }
    return board[row][col]->piece->getType();
}


bool BoardDisplay::simulateInCheck(Piece* p, char newC, int newI) {
    // Save the current position and temporarily move the piece
    auto currentPosition = p->getPosition();
    Piece* tempCapture = board[newI - 1][newC - 'a']->piece;
    setState(p, newC, newI);
    setState(nullptr, currentPosition.first, currentPosition.second);

    // Check if the king is in check after the move
    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer.get() : whitePlayer.get();
    PlayerInfo* oppositePlayer = (p->getColour() == BLACK) ? whitePlayer.get() : blackPlayer.get();

    bool originalCheckState = currentPlayer->inCheck;
    currentPlayer->inCheck = false;
    bool remainsInCheck = false;
    for (const auto& piece : oppositePlayer->activePieces) {
        if (piece->isValidMove(currentPlayer->kingPosition.first, currentPlayer->kingPosition.second)) {
            remainsInCheck = true;
            break;
        }
    }
    currentPlayer->inCheck = originalCheckState;

    // Restore the board to its original state
    setState(tempCapture, newC, newI);
    setState(p, currentPosition.first, currentPosition.second);

    return remainsInCheck;
}
