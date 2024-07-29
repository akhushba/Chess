#include "boarddisplay.h"

#include "colour.h"
#include "piece.h"
#include "player.h"

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

#include "human.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"

BoardDisplay::BoardSegment::BoardSegment(Colour c) : colour{c}, piece{nullptr} {}

void BoardDisplay::BoardSegment::setBegin() {
    piece = nullptr;
}

BoardDisplay::PlayerInfo::PlayerInfo(Colour c, char kingC, int kingI, string playerType)
                : score{0}, colour{c}, inCheck{false} {
    if(playerType == "human") {

    } else if (playerType == "computer1") {

    } else if (playerType == "computer2") {

    } else if (playerType == "computer3") {

    } else if (playerType == "computer4") {

    } 
}

// Initialize the board with unique pointers to BoardSegment
void BoardDisplay::init() {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            Colour segmentColor = ((i + j) % 2 == 0) ? WHITE : BLACK;
            board[i][j] = std::make_unique<BoardSegment>(segmentColor);
        }
    }

    whitePlayer = std::make_unique<PlayerInfo>(Colour::WHITE, 'e', 1, 'human');
    blackPlayer = std::make_unique<PlayerInfo>(Colour::BLACK, 'e', 8, 'human');
    getCurrentTurn = WHITE;
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

void BoardDisplay::addPiece(char type, string pos) {
    Colour c = std::islower(type) ? BLACK : WHITE;
    char cPos = pos[0];
    int iPos = (int)pos[1];

    std::unique_ptr<Piece> newPiece;
        if (type == 'Q' || type == 'q') {
            newPiece = std::make_unique<Queen>(c, nullptr, cPos, iPos);
        } else if (type == 'R'  || type == 'r') {
            newPiece = std::make_unique<Rook>(c, nullptr, cPos, iPos);
        } else if (type == 'B'  || type == 'b') {
            newPiece = std::make_unique<Bishop>(c, nullptr, cPos, iPos);
        } else if (type == 'N'  || type == 'n') {
            newPiece = std::make_unique<Knight>(c, nullptr, cPos, iPos);
        } else if (type == 'N'  || type == 'n') {
            newPiece = std::make_unique<Queen>(c, nullptr, cPos, iPos);
        } else if (type == 'K'  || type == 'k') {
            newPiece = std::make_unique<King>(c, nullptr, cPos, iPos);
        } else if (type == 'P'  || type == 'p') {
            newPiece = std::make_unique<Pawn>(c, nullptr, cPos, iPos);
        }
    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer.get() : whitePlayer.get();
    setState(newPiece.get(), cPos, iPos);
    currentPlayer->activePieces.push_back(std::move(newPiece));
}

void BoardDisplay::removePiece(string pos) {
    Piece* p = board[(int)pos[1] - 1][pos[0] - 'a']->piece;
    if(p) {
        PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer.get() : whitePlayer.get();
        auto& activePieces = currentPlayer->activePieces;
        auto it = std::find_if(activePieces.begin(), activePieces.end(),
            [&p](const std::unique_ptr<Piece>& piece) {
                return piece.get() == p;
            });
        if (it != activePieces.end()) {
            currentPlayer->inactivePieces.push_back(std::move(*it));
            activePieces.erase(it);
        }
    }
}

// Set the state of a board segment
void BoardDisplay::setState(Piece* p, char cPos, int iPos, char pawnPromote) {

    char type = p->getType();
    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer.get() : whitePlayer.get();
    if(type == 'k' || type == 'K') {
        if(abs(p->getPosition().first - cPos) == 2) {
            if(p->getColour() == WHITE) {
                setState(board[1-1]['h'-'a']->piece, 'f', 1);
            } else {
                setState(board[8-1]['h'-'a']->piece, 'f', 8);
            }
        }
        currentPlayer->kingPosition = {cPos, iPos};
    } else if (type == 'p' || type == 'P') {
        // Handle pawn promotion
        if ((p->getColour() == WHITE && iPos == 8) || (p->getColour() == BLACK && iPos == 1)) {
            // Move the current pawn to inactivePieces
            auto& activePieces = currentPlayer->activePieces;
            auto it = std::find_if(activePieces.begin(), activePieces.end(),
                [&p](const std::unique_ptr<Piece>& piece) {
                    return piece.get() == p;
                });
            if (it != activePieces.end()) {
                currentPlayer->inactivePieces.push_back(std::move(*it));
                activePieces.erase(it);
            }
            std::string combinedP(1, cPos);  // Create a string with the first char
            combinedP += (char)iPos;              
            addPiece(pawnPromote, combinedP);
            board[iPos - 1][cPos - 'a']->piece = p;
            p->setPos(cPos, iPos);
            return;
        }
    }

    Piece* capturePiece = board[iPos - 1][cPos - 'a']->piece;
    if(capturePiece) {
        auto& activePieces = currentPlayer->activePieces;
        auto it = std::find_if(activePieces.begin(), activePieces.end(),
            [&capturePiece](const std::unique_ptr<Piece>& piece) {
                return piece.get() == capturePiece;
            });
        if (it != activePieces.end()) {
            currentPlayer->inactivePieces.push_back(std::move(*it));
            activePieces.erase(it);
        }
    }

    board[iPos - 1][cPos - 'a']->piece = p;
    p->setPos(cPos, iPos);
    p->hasMoved = true;
}

bool BoardDisplay::canCapture(Colour pieceColour, char cPos, int iPos) {
    
}

bool BoardDisplay::canCastle(Colour c) {
    if(customSetup) return false;

    if(c == WHITE) {
        Piece* potentialKing = board[1-1]['e'-'a']->piece;
        Piece* potentialRook = board[1-1]['h'-'a']->piece;
        if(!potentialKing && potentialKing->getType() != 'K' && !potentialKing->hasMoved) 
            return false;
        else if(!potentialRook && potentialRook->getType() != 'R' && !potentialRook->hasMoved) 
            return false;
        else if (board[1-1]['f'-'a']->piece != nullptr || board[1-1]['g'-'a']->piece != nullptr) 
            return false;
    } else {
        Piece* potentialKing = board[8-1]['e'-'a']->piece;
        Piece* potentialRook = board[8-1]['h'-'a']->piece;
        if(!potentialKing && potentialKing->getType() != 'k' && !potentialKing->hasMoved) 
            return false;
        else if(!potentialRook && potentialRook->getType() != 'r' && !potentialRook->hasMoved) 
            return false;
        else if (board[8-1]['f'-'a']->piece != nullptr || board[8-1]['g'-'a']->piece != nullptr) 
            return false;
    }

    return true;
}


Colour BoardDisplay::occupied(char c, int i) {
    BoardSegment* seg = getBoardInfo(c, i);
    if(seg->piece) return seg->piece->getColour();
    else return NULL_C;
}

bool BoardDisplay::simulateAttack(Piece* p, char newC, int newI, Piece* checkAttack) {
    pair<char, int> currentPosition = p->getPosition();

    Piece* tempCapture = getBoardInfo(newC, newI)->piece;
    setState(p, newC, newI);
    setState(nullptr, currentPosition.first, currentPosition.second);

    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer.get() : whitePlayer.get();
    PlayerInfo* oppositePlayer = (p->getColour() == BLACK) ? whitePlayer.get() : blackPlayer.get();

    bool canBeAttacked = false;
    bool originalCheckState = currentPlayer->inCheck;
    currentPlayer->inCheck = false;

    for(const auto& piece : oppositePlayer->activePieces) {
        if (checkAttack) {
            canBeAttacked = piece->isValidMove(checkAttack->getPosition().first, checkAttack->getPosition().second);
        } else {
            canBeAttacked = piece->isValidMove(currentPlayer->kingPosition.first, currentPlayer->kingPosition.second);
        }
        if(canBeAttacked) break;
    }

    currentPlayer->inCheck = originalCheckState;
    
    setState(tempCapture, newC, newI);
    setState(p, currentPosition.first, currentPosition.second);

    return canBeAttacked;
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
bool BoardDisplay::inStalemate(Colour c) {
    // king is not in check since that would get triggered in checkmate
    // no piece can be moved without putting the king in check 
    // need to check to see if all no valid pos moves exist
    if (inCheck(c)){
        return false;
    }
    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer.get() : whitePlayer.get();
    for (auto& p : currentPlayer -> activePieces){
         if(!p->validPosVec.empty()) {
            return false;
         }
    }
    return true;
}

void BoardDisplay::setUpGame(){
        string setupCommand;
        while(cin >> setupCommand) {
            if(setupCommand == "+"){
                char addnewPiece;
                string addPos;
                cin >> addnewPiece >> addPos;
                addPiece(addnewPiece, addPos);
            }
            else if(setupCommand == "-"){
                string removePos;
                cin >> removePos;
                removePiece(removePos);
            }
            else if(setupCommand == "="){
                string colour;
                cin >> colour;
                if(colour == "WHITE"){
                   getCurrentTurn = WHITE;
                }
                if(colour == "Black"){
                    getCurrentTurn = BLACK;
                }
            }
            else if(setupCommand == "done"){
                break;
            }
        }
}
void BoardDisplay::resign(Colour c) {
    //if black resigns, then white gets +1 score and game ends vice versa if white resigns
    PlayerInfo* winningPlayer = (c == BLACK) ? whitePlayer.get() : blackPlayer.get();
    winningPlayer->score++;

    endGame();
    notifyObservers();

}

void BoardDisplay::PlayerInfo::reset() {
    inCheck = false;
    kingPosition = (colour == WHITE) ? make_pair('e', 1) :  make_pair('e', 8);
}

void BoardDisplay::endGame() {
    //need to reset the player info 
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            Colour segmentColor = ((i + j) % 2 == 0) ? WHITE : BLACK;
            board[i][j] -> setBegin();
        }
    }


    getWhitePlayer()->reset();
    getBlackPlayer()->reset();

    notifyObservers();
}

void BoardDisplay::endSession() {
    notifyObservers();
}


BoardDisplay::PlayerInfo* BoardDisplay::getWhitePlayer() {
    return whitePlayer.get();
}

BoardDisplay::PlayerInfo* BoardDisplay::getBlackPlayer() {
    return blackPlayer.get();
}

BoardDisplay::PlayerInfo* BoardDisplay::getCurrentPlayer() {
    return getCurrentTurn == WHITE ? whitePlayer.get() : blackPlayer.get();
}

void BoardDisplay::addWhitePlayer(string playerType) {
    whitePlayer = make_unique<PlayerInfo>(WHITE, 'e', 'f', playerType);
}

void BoardDisplay::addBlackPlayer(string playerType) {
    blackPlayer = make_unique<PlayerInfo>(BLACK, 'e', 'f', playerType);
        
}