#include "boarddisplay.h"
#include <memory>

// Initialize the board with unique pointers to BoardSegment
void BoardDisplay::init() {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            Colour segmentColor = ((i + j) % 2 == 0) ? WHITE : BLACK;
            board[i][j] = std::make_unique<BoardSegment>(segmentColor);
        }
    }

    whitePlayer = std::make_unique<PlayerInfo>(Colour::WHITE, 'e', 1);
    blackPlayer = std::make_unique<PlayerInfo>(Colour::BLACK, 'e', 8);

}

BoardDisplay::BoardSegment* BoardDisplay::getBoardInfo(char c, int i) {
    return board[i - 1][c - 'a'].get();
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
    if (!board[row][col]->piece) {
        return board[row][col]->colour == BLACK ? '_' : ' ';
    }
    return board[row][col]->piece->getType();
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

bool BoardDisplay::canCapture(Colour pieceColour, char cPos, int iPos) {
    
}

Colour BoardDisplay::occupied(char c, int i) {
    BoardSegment* seg = getBoardInfo(c, i);
    if(seg->piece) return seg->piece->getColour();
    else return NULL_C;
}

bool BoardDisplay::simulateInCheck(Piece* p, char newC, int newI) {
    // Save the current position and temporarily move the piece
    auto currentPosition = p->getPosition();
    Piece* tempCapture = getBoardInfo(newC, newI)->piece;
    setState(p, newC, newI);
    setState(nullptr, currentPosition.first, currentPosition.second);

    // Check if the king is in check after the move
    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer.get() : whitePlayer.get();
    PlayerInfo* oppositePlayer = (p->getColour() == BLACK) ? whitePlayer.get() : blackPlayer.get();

    bool originalCheckState = currentPlayer->inCheck;
    currentPlayer->inCheck = false;
    bool remainsInCheck = false;
    for (const auto& piece : oppositePlayer->activePieces) {
        if (piece.get()->isValidMove(currentPlayer->kingPosition.first, currentPlayer->kingPosition.second)) {
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

bool BoardDisplay::inCheck(Colour c) {
    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer.get() : whitePlayer.get();
    PlayerInfo* oppositePlayer = (c == BLACK) ? whitePlayer.get() : blackPlayer.get();

    bool inCheck = false;
    for(auto& p : oppositePlayer->activePieces) {
        if(p.get()->isValidMove(currentPlayer->kingPosition.first, currentPlayer->kingPosition.second)) inCheck = true;
    }
    return inCheck;
}

bool BoardDisplay::inCheckmate(Colour c) {
    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer.get() : whitePlayer.get();
    bool allEmpty = true;
    for(auto& p : currentPlayer->activePieces) {
        p.get()->generateMoves();
        if(!p.get()->validPosVec.empty()) allEmpty = false;
    }
    return allEmpty;
}

void BoardDisplay::resign() {

}

void BoardDisplay::endGame() {
    
}

void BoardDisplay::endSession() {
    
}
