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

#include "textdisplay.h"
#include "graphicsdisplay.h"

BoardDisplay::BoardSegment::BoardSegment(Colour c) : colour{c}, piece{nullptr} {}

void BoardDisplay::BoardSegment::setBegin() {
    piece = nullptr;
}

BoardDisplay::PlayerInfo::PlayerInfo(Colour c, char kingC, int kingI)
    : player(nullptr), score{0}, colour{c}, inCheck{false}, kingPosition{kingC, kingI} {
}

// Initialize the board
void BoardDisplay::init() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Colour segmentColor = ((i + j) % 2 == 0) ? BLACK : WHITE;
            board[i][j] = new BoardSegment(segmentColor);
        }
    }

    whitePlayer = new PlayerInfo(Colour::WHITE, 'e', 1);
    blackPlayer = new PlayerInfo(Colour::BLACK, 'e', 8);
    getCurrentTurn = WHITE;

    // White pieces
    addPiece('R', "a1"); // Rook
    addPiece('N', "b1"); // Knight
    addPiece('B', "c1"); // Bishop
    addPiece('Q', "d1"); // Queen
    addPiece('K', "e1"); // King
    addPiece('B', "f1"); // Bishop
    addPiece('N', "g1"); // Knight
    addPiece('R', "h1"); // Rook
    addPiece('P', "a2"); // Pawns
    addPiece('P', "b2");
    addPiece('P', "c2");
    addPiece('P', "d2");
    addPiece('P', "e2");
    addPiece('P', "f2");
    addPiece('P', "g2");
    addPiece('P', "h2");

    // Black pieces
    addPiece('r', "a8"); // Rook
    addPiece('n', "b8"); // Knight
    addPiece('b', "c8"); // Bishop
    addPiece('q', "d8"); // Queen
    addPiece('k', "e8"); // King
    addPiece('b', "f8"); // Bishop
    addPiece('n', "g8"); // Knight
    addPiece('r', "h8"); // Rook
    addPiece('p', "a7"); // Pawns
    addPiece('p', "b7");
    addPiece('p', "c7");
    addPiece('p', "d7");
    addPiece('p', "e7");
    addPiece('p', "f7");
    addPiece('p', "g7");
    addPiece('p', "h7");

}

Piece* BoardDisplay::getBoardInfo(char c, int i) {
    return board[i - 1][c - 'a']->piece;
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
    int iPos = pos[1] - '0';
    int countWhite;
    int countBlack;
    Piece* newPiece = nullptr;
    if(cPos < 'a' || cPos > 'h' || iPos < 1 || iPos > 8) 
        return;
    if (type == 'Q' || type == 'q') {
        newPiece = new Queen(c, nullptr, cPos, iPos);
    } else if (type == 'R' || type == 'r') {
        newPiece = new Rook(c, nullptr, cPos, iPos);
    } else if (type == 'B' || type == 'b') {
        newPiece = new Bishop(c, nullptr, cPos, iPos);
    } else if (type == 'N' || type == 'n') {
        newPiece = new Knight(c, nullptr, cPos, iPos);
    } else if (type == 'K' || type == 'k') {
        if(c == BLACK && countBlack == 1 || c == WHITE && countWhite ==1){
            cout << "invalid number of kings"<<endl;
            return;
        }
        if (inCheck(c)){
            cout<<"invalid, king is incheck"<<endl;
        }
        newPiece = new King(c, nullptr, cPos, iPos);
        if (c == WHITE){
            countWhite += 1;
        }
        else{
            countBlack += 1;    
        }  

        //need to make sure neither kings are in check
        //exactly one black king and one white king

    }  else if (type == 'P' || type == 'p') {
        cout << "AHHAFHAHSD \t" << cPos << iPos << endl;
        if('a' <= cPos && cPos >= 'h' && 2 <= iPos && iPos >= 7){
        //ensure that no pawns are in the first or last row of board
        newPiece = new Pawn(c, nullptr, cPos, iPos);
        }
        else{
            cout<<"invalid placement of pawn"<<endl;
        }
    }

    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
    setState(newPiece, cPos, iPos);
    currentPlayer->activePieces.push_back(newPiece);
}

void BoardDisplay::removePiece(string pos) {
    Piece* p = board[pos[1] - '0' - 1][pos[0] - 'a']->piece;
    if (p) {
        PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer : whitePlayer;
        auto& activePieces = currentPlayer->activePieces;
        auto it = std::find(activePieces.begin(), activePieces.end(), p);
        if (it != activePieces.end()) {
            currentPlayer->inactivePieces.push_back(*it);
            activePieces.erase(it);
        }
    }
}

void BoardDisplay::setState(Piece* p, char cPos, int iPos, char pawnPromote) {
    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer : whitePlayer;

    if (p->getType() == 'K' || p->getType() == 'k') {
        currentPlayer->kingPosition = {cPos, iPos};
    }

    board[iPos - 1][cPos - 'a']->piece = p;
    if (p) {
        p->setPos(cPos, iPos);
        p->hasMoved = true;
    }
}

bool BoardDisplay::canCapture(Colour pieceColour, char cPos, int iPos) {
    Piece* piece = getBoardInfo(cPos, iPos);
    return piece && piece->getColour() != pieceColour;
}

bool BoardDisplay::canCastle(Colour c) {
    if (customSetup) return false;

    if (c == WHITE) {
        Piece* king = getBoardInfo('e', 1);
        Piece* rook = getBoardInfo('h', 1);
        if (!king || king->getType() != 'K' || king->hasMoved) return false;
        if (!rook || rook->getType() != 'R' || rook->hasMoved) return false;
        if (getBoardInfo('f', 1) || getBoardInfo('g', 1)) return false;
    } else {
        Piece* king = getBoardInfo('e', 8);
        Piece* rook = getBoardInfo('h', 8);
        if (!king || king->getType() != 'k' || king->hasMoved) return false;
        if (!rook || rook->getType() != 'r' || rook->hasMoved) return false;
        if (getBoardInfo('f', 8) || getBoardInfo('g', 8)) return false;
    }

    return true;
}

Colour BoardDisplay::occupied(char c, int i) {
    Piece* p = getBoardInfo(c, i);
    if (p) return p->getColour();
    return NULL_C;
}


bool BoardDisplay::simulateAttack(Piece* p, char newC, int newI, Piece* checkAttack) {
    pair<char, int> currentPosition = p->getPosition();

    Piece* tempCapture = getBoardInfo(newC, newI);
    setState(p, newC, newI);
    setState(nullptr, currentPosition.first, currentPosition.second);

    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer : whitePlayer;
    PlayerInfo* oppositePlayer = (p->getColour() == BLACK) ? whitePlayer : blackPlayer;

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
    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
    PlayerInfo* oppositePlayer = (c == BLACK) ? whitePlayer : blackPlayer;

    for (auto& p : oppositePlayer->activePieces) {
        if (p->isValidMove(currentPlayer->kingPosition.first, currentPlayer->kingPosition.second)) return true;
    }
    return false;
}


bool BoardDisplay::inCheckmate(Colour c) {
    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
    for (auto& p : currentPlayer->activePieces) {
        p->generateMoves();
        if (!p->validPosVec.empty()) return false;
    }
    return true;
}

    // king is not in check since that would get triggered in checkmate
    // no piece can be moved without putting the king in check 
    // need to check to see if all no valid pos moves exist
bool BoardDisplay::inStalemate(Colour c) {
    if (inCheck(c)) return false;

    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
    for (auto& p : currentPlayer->activePieces) {
        if (!p->validPosVec.empty()) return false;
    }
    return true;
}


void BoardDisplay::setUpGame() {
    string setupCommand;
    while (cin >> setupCommand) {
        if (setupCommand == "+") {
            char addnewPiece;
            string addPos;
            cin >> addnewPiece >> addPos;
            addPiece(addnewPiece, addPos);
        } else if (setupCommand == "-") {
            string removePos;
            cin >> removePos;
            removePiece(removePos);
        } else if (setupCommand == "=") {
            string colour;
            cin >> colour;
            getCurrentTurn = (colour == "WHITE") ? WHITE : BLACK;
        } else if (setupCommand == "done") {
            notifyObservers();
            break;
        }
        notifyObservers();
    }
}

//if black resigns, then white gets +1 score and game ends vice versa if white resigns
void BoardDisplay::resign(Colour c) {
    PlayerInfo* winningPlayer = (c == BLACK) ? whitePlayer : blackPlayer;
    winningPlayer->score++;
    endGame();
    notifyObservers();
}

void BoardDisplay::PlayerInfo::reset() {
    inCheck = false;
    kingPosition = (colour == WHITE) ? make_pair('e', 1) : make_pair('e', 8);
}


void BoardDisplay::endGame() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j]->setBegin();
        }
    }
    whitePlayer->reset();
    blackPlayer->reset();
    customSetup = false;
    notifyObservers();
}

void BoardDisplay::endSession() {
    notifyObservers();
}


void BoardDisplay::makeMove(Colour c, string oldPos, string newPos){
        PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
        Piece* p = getBoardInfo(oldPos[0], (int)oldPos[1]);
        currentPlayer->player->move(p, newPos[0], (int)newPos[1]);
}

BoardDisplay::PlayerInfo* BoardDisplay::getWhitePlayer() {
    return whitePlayer;
}

BoardDisplay::PlayerInfo* BoardDisplay::getBlackPlayer() {
    return blackPlayer;
}

BoardDisplay::PlayerInfo* BoardDisplay::getCurrentPlayer() {
    return getCurrentTurn == WHITE ? whitePlayer : blackPlayer;
}

BoardDisplay::BoardDisplay() {
    init();
    attach(new TextDisplay(this));
    notifyObservers();

}

void BoardDisplay::setPlayer(Colour c, string playerType) {
    Player* p = c == WHITE ? whitePlayer->player : blackPlayer->player;
    if(p) delete p;
    if (playerType == "human") {
        p = new Human("human", {});
    } else if (playerType == "computer1") {
        p = new LevelOne("level one", {});
    } else if (playerType == "computer2") {
        p = new LevelTwo("level two", {});
    } else if (playerType == "computer3") {
        p = new LevelThree("level three", {});
    } else if (playerType == "computer4") {
        p = new LevelFour("level four", {});
    }
}

void BoardDisplay::setPlayers(string playerOne, string playerTwo) {
    setPlayer(WHITE, playerOne);
    setPlayer(BLACK, playerTwo);
}