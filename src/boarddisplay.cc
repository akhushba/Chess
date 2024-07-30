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

// defaultBoardialize the board
void BoardDisplay::defaultBoard() {
    // White pieces
    addPiece('R', "a1"); // Rook
    addPiece('B', "c1"); // Bishop
    addPiece('Q', "d1"); // Queen
    addPiece('K', "e1"); // King
    addPiece('B', "f1"); // Bishop
    addPiece('R', "h1"); // Rook
    addPiece('N', "b1"); // Knight
    addPiece('N', "g1"); // Knight
    addPiece('P', "b2");
    addPiece('P', "a2"); // Pawns
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

    customSetup = false;
    notifyObservers();
}

Piece* BoardDisplay::getBoardInfo(char c, int i) {
    // cout << i-1 << ", " << c-'a' << endl;
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

void BoardDisplay::addPiece(char type, const std::string pos) {
    Colour c = std::islower(type) ? BLACK : WHITE;
    char cPos = pos[0];
    int iPos = pos[1] - '0'; // Convert char to int

    // Check for valid positions
    if (iPos < 1 || iPos > 8 || cPos < 'a' || cPos > 'h') {
        cout << "Invalid position: " << pos << endl;
        return;
    }

    int countWhite;
    int countBlack;

    Piece* newPiece = nullptr;
    switch (type) {
        case 'Q': case 'q': newPiece = new Queen(c, this, cPos, iPos); break;
        case 'R': case 'r': newPiece = new Rook(c, this, cPos, iPos); break;
        case 'B': case 'b': newPiece = new Bishop(c, this, cPos, iPos); break;
        case 'N': case 'n': newPiece = new Knight(c, this, cPos, iPos); break;
        case 'K': case 'k': 
            // if ((c == BLACK && countBlack >= 1) || (c == WHITE && countWhite >= 1)) {
            //     cout << "Invalid number of kings" << endl;
            //     return;
            // }
            // if (inCheck(c)) {
            //     cout << "Invalid, king is in check" << endl;
            //     return;
            // }
            newPiece = new King(c, this, cPos, iPos);
            // (c == WHITE ? countWhite : countBlack)++;
            break;
        case 'P': case 'p':
            if (iPos == 1 || iPos == 8) {
                cout << "Invalid placement of pawn" << endl;
                return;
            }
            newPiece = new Pawn(c, this, cPos, iPos);
            break;
        default:
            cout << "Unknown piece type: " << type << endl;
            return;
    }

    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
    // if(canCapture(WHITE, cPos, iPos) || canCapture(WHITE, cPos, iPos)) removePiece(cPos, iPos);
    if(!getBoardInfo(cPos, iPos))
    board[iPos - 1][cPos - 'a']->piece = newPiece;
    else throw runtime_error ("piece already exists here, may not add");
    currentPlayer->activePieces.push_back(newPiece);
    // currentPlayer->player->pieceSet.push_back(newPiece);

}


void BoardDisplay::removePiece(char cPos, int iPos) {
    Piece* p = board[iPos - 1][cPos - 'a']->piece;
    // cout << "removing from " << cPos << iPos << endl;
    if (p) {
        PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer : whitePlayer;
        // cout << "----------" << currentPlayer->activePieces.size() << endl;
        auto& activePieces = currentPlayer->activePieces;
        auto it = std::find(activePieces.begin(), activePieces.end(), p);
        if (it != activePieces.end()) {
            currentPlayer->inactivePieces.push_back(*it);
            activePieces.erase(it);
        }
        // setState(nullptr, pos[0], pos[1]-'0');
        // cout << "----------" << currentPlayer->activePieces.size() << endl;
    }
}

void BoardDisplay::setState(Piece* p, char cPos, int iPos) {

    if (p) {
        Colour col = p->getColour();
        PlayerInfo* currentPlayer = (col == BLACK) ? blackPlayer : whitePlayer;
        if (p->getType() == 'K' || p->getType() == 'k') {
            currentPlayer->kingPosition = {cPos, iPos};
            if(canCastle(col) && abs(cPos - p->getPosition().first) == 2) {
                if(col == WHITE) {
                    setState(getBoardInfo('h', 1), 'f', 1);
                    setState(nullptr, 'h', 1);
                }
                else {
                    setState(getBoardInfo('h', 8), 'f', 8);
                    setState(nullptr, 'h', 8);
                }
            }
        } else if ((p->getType() == 'P' || p->getType() == 'p')) {
            if((col == BLACK && iPos == 1) || (col == WHITE && iPos == 8)){
                char c;
                if(cin >> c) {
                    delete p;
                    switch(c) {
                        case 'Q': case 'q': p = new Queen(col, this, cPos, iPos); break;
                        case 'R': case 'r': p = new Rook(col, this, cPos, iPos); break;
                        case 'B': case 'b': p = new Bishop(col, this, cPos, iPos); break;
                        case 'N': case 'n': p = new Knight(col, this, cPos, iPos); break;
                        default: throw runtime_error("wrong pawn promotion type");
                    }
                } else throw runtime_error("expected pawn promotion");
            }
        }
        if(canCapture(col, p->getPosition().first, p->getPosition().second)) {
            cout << "CAPTURONG AH " << endl;
            removePiece(cPos, iPos);
        }
        p->setPos(cPos, iPos);
        p->hasMoved = true;
    }
    board[iPos - 1][cPos - 'a']->piece = p;
}

bool BoardDisplay::canCapture(Colour pieceColour, char cPos, int iPos) {
    Piece* piece = getBoardInfo(cPos, iPos);
    if(!piece) return false;
    else if(piece && piece->getColour() == pieceColour)  return false;
    return true;
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
    if(p) return p->getColour();
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
        if (checkValid(p, currentPlayer->kingPosition.first, currentPlayer->kingPosition.second)) 
        return true;

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
            removePiece(removePos[0],removePos[1]-'0');
        } else if (setupCommand == "=") {
            string colour;
            cin >> colour;
            getCurrentTurn = (colour == "WHITE") ? WHITE : BLACK;
        } else if (setupCommand == "done") {
            notifyObservers();
            customSetup = true;
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

vector<pair<char, int>> BoardDisplay::getValidMoves(Piece* p) {
    vector<pair<char, int>> validMoves = {};
    vector<pair<char, int>> moves = p->generate();
    for(auto& m : moves) {
        // cout << "ingetvalidmoves: " << p->getType() << " " << p->getPosition().first << p->getPosition().second << "\t" << m.first << m.second << endl;
        if(p->getType() == 'N' || p->getType() == 'n') {
            if(occupied(m.first, m.second) == p->getColour()) continue;
        } else {
            char currC = p->getPosition().first;
            int currI = p->getPosition().second;
            // check all square in between
            // Determine movement direction
            int colDiff = m.first - currC;
            int rowDiff = m.second - currI;
            int colStep = (colDiff == 0) ? 0 : (colDiff > 0) ? 1 : -1;
            int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0) ? 1 : -1;

            //make sure all squares inbetween are unoccupied
            char currentCol = currC;  // Start with the next position
            int currentRow = currI ;

            while (currentCol != m.first || currentRow != m.second) {
                currentCol += colStep;
                currentRow += rowStep;
                // cout << currentCol << currentRow << "\t" << occupied(currentCol, currentRow) << endl;
                if (occupied(currentCol, currentRow) == p->getColour()) goto checkMore;
                if ((p->getType() == 'P' || p->getType() == 'p') && colDiff != 0 && occupied(currentCol, currentRow) == NULL_C) goto checkMore;
            }

        }
        
        if(simulateAttack2(p, m.first, m.second)) continue;
        // run in check simulation
        if(p->getType() == 'K' || p->getType() == 'k') {
            if (canCastle(p->getColour())) {
                if (p->getColour() == WHITE && m.first == 'g' && m.second == 1) { 
                    validMoves.emplace_back(m);
                    // cout << "placing1: " << p->getType() << " " << p->getPosition().first << p->getPosition().second << "\t" << m.first << m.second << endl;
                    continue;
                } else if (p->getColour() == BLACK && m.first == 'g' && m.second == 8)  {
                    validMoves.emplace_back(m);
                    // cout << "placing2: " << p->getType() << " " << p->getPosition().first << p->getPosition().second << "\t" << m.first << m.second << endl;
                    continue;
                }
                else continue;
            }
        }

        validMoves.emplace_back(m);
        // cout << "placing3: " << p->getType() << " " << p->getPosition().first << p->getPosition().second << "\t" << m.first << m.second << endl;
        checkMore: continue;
    }
    return validMoves;
}


void BoardDisplay::makeMove(Colour c){

    PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
    vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves;
    vector<pair<char, int>> moves;
    pair<Piece*, pair<char, int>> pieceMovePair;
    cout << "HERERE W " << endl;
    if (currentPlayer->player->getName() == "human") {
        string oldPos, newPos;
        cin >> oldPos >> newPos;
        Piece* p = getBoardInfo(oldPos[0], oldPos[1]-'0');

        if(checkValid(p, newPos[0], newPos[1]-'0')) {
            setState(p,newPos[0], newPos[1]-'0');
            setState(nullptr,oldPos[0], oldPos[1]-'0');
        }
    } else {
        // for(auto& active : currentPlayer->activePieces) {
        //     for (auto& pair : active->generate()) {
        //     }
        // }
        int count = 0;
        for (auto& active : currentPlayer->activePieces) {
                // cout << "VALID MOVES FOR: " << active->getType() << " " << active->getPosition().first << active->getPosition().second << endl;
            vector<pair<char, int>> gotMoves = getValidMoves(active);
            for (auto& pair : gotMoves) {
                // cout << pair.first << pair.second << endl;
            }
            count++;
            if (gotMoves.size() != 0) {
                pieceAndMoves.emplace_back(make_pair(active, gotMoves));
            }
        }
        for(auto& pm : pieceAndMoves) {
            cout << "FOR: \t"<< pm.first->getType() << " " << pm.first->getPosition().first << pm.first->getPosition().second << endl << "\thas:" << endl;
            for(auto& pmp : pm.second){
                cout << "\t\t" << pmp.first << pmp.second << endl;
            }
        }
        // cout << "------" << endl;
        pieceMovePair = currentPlayer->player->move(pieceAndMoves, {});
        // cout << "+++++++++++++++" << endl;
        Piece* movePiece = get<0>(pieceMovePair);
        char oldC = movePiece->getPosition().first;
        int oldI = movePiece->getPosition().second;
        char moveC = get<0>(get<1>(pieceMovePair));
        int moveI = get<1>(get<1>(pieceMovePair));
        setState(movePiece, moveC, moveI);

        setState(nullptr, oldC, oldI);
        // do this later
        // setState(nullptr,oldPos[0], oldPos[1]-'0');
    }

    // if(checkValid(p, newPos[0], newPos[1]-'0')) {
    //     setState(p,newPos[0], newPos[1]-'0');
    //     setState(nullptr,oldPos[0], oldPos[1]-'0');
    // }
    // else
    // currentPlayer->player->move(p, newPos[0], (int)newPos[1]);
    cout << "++++++++++4" << endl;
    //ADD PAWN PROMOTION
    notifyObservers();
}

// void BoardDisplay::makeMove(Colour c){

//     PlayerInfo* currentPlayer = (c == BLACK) ? blackPlayer : whitePlayer;
//     vector<pair<Piece*, vector<pair<char, int>>>> pieceAndMoves;
//     vector<pair<Piece*, vector<pair<char, int>>>> pieceAndCaptureMoves;
//     vector<pair<char, int>> moves;
//     vector<pair<char, int>> captureMoves;
//     pair<Piece*, pair<char, int>> pieceMovePair;

//     if (currentPlayer->player->getName() == "human") {
//         string oldPos, newPos;
//         cin >> oldPos >> newPos;
//         Piece* p = getBoardInfo(oldPos[0], oldPos[1]-'0');

//         if(checkValid(p, newPos[0], newPos[1]-'0')) {
//             setState(p,newPos[0], newPos[1]-'0');
//             setState(nullptr,oldPos[0], oldPos[1]-'0');
//         }
//     } else {
//         for (auto& active : currentPlayer->activePieces) {
//             for (auto& pair : active->generate()) {
//                 cout << get<0>(pair) << ", " << get<1>(pair) << endl;
//                 if (checkValid(active, get<0>(pair), get<1>(pair))) {
//                     moves.emplace_back(make_pair(get<0>(pair), get<1>(pair)));
//                 }
//                 if (canCapture(c, get<0>(pair), get<1>(pair))) {
//                     captureMoves.emplace_back(make_pair(get<0>(pair), get<1>(pair)));
//                 }
//             }
//             if (moves.size() != 0) pieceAndMoves.emplace_back(make_pair(active, moves));
//             if (captureMoves.size() != 0) pieceAndCaptureMoves.emplace_back(make_pair(active, captureMoves));
//             moves.clear(); 
//         }
//         cout << "------" << endl;

//         pieceMovePair = currentPlayer->player->move(pieceAndMoves, pieceAndCaptureMoves);

//         cout << "+++++++++++++++" << endl;
//         Piece* movePiece = get<0>(pieceMovePair);
//         char oldC = movePiece->getPosition().first;
//         int oldI = movePiece->getPosition().second;
//         char moveC = get<0>(get<1>(pieceMovePair));
//         int moveI = get<1>(get<1>(pieceMovePair));
//         setState(movePiece, moveC, moveI);
//         setState(nullptr, oldC, oldI);
//     }
//     cout << "++++++++++4" << endl;
//     //ADD PAWN PROMOTION
//     notifyObservers();
// }

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
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Colour segmentColor = ((i + j) % 2 == 0) ? BLACK : WHITE;
            board[i][j] = new BoardSegment(segmentColor);
        }
    }

    whitePlayer = new PlayerInfo(Colour::WHITE, 'e', 1);
    blackPlayer = new PlayerInfo(Colour::BLACK, 'e', 8);
    getCurrentTurn = WHITE;

    attach(new TextDisplay(this));
    // attach(new GraphicsDisplay(this));
    notifyObservers();
}

Player* BoardDisplay::setPlayer(Colour c, string playerType) {
    Player* p = c == WHITE ? whitePlayer->player : blackPlayer->player;
    if(p) delete p;
    if (playerType == "human") {
        p = new Human("human", {}, c);
    } else if (playerType == "computer1") {
        p = new LevelOne("level one", {}, c);
    } else if (playerType == "computer2") {
        p = new LevelTwo("level two", {}, c);
    } else if (playerType == "computer3") {
        p = new LevelThree("level three", {},c );
    } else if (playerType == "computer4") {
        p = new LevelFour("level four", {}, c);
    }
    return p;
}

void BoardDisplay::setPlayers(string playerOne, string playerTwo) {
    whitePlayer->player = setPlayer(WHITE, playerOne);
    blackPlayer->player = setPlayer(BLACK, playerTwo);
}

bool BoardDisplay::checkValid(Piece* p, char cPos, int iPos){
    if(!p) return false;
    vector<pair<char,int>> possible = p->generate();
    //find pair <cpos,iPos>
    auto foundPair = findPair(possible, cPos, iPos);
    if (foundPair.first == 'i') {
        // cout << "invalid move" << endl;
        return false;
    }
    cout << foundPair.first << foundPair.second << endl;
    if(p->getType() == 'N' || p->getType() == 'n') {
        //only check end
        if(occupied(cPos, iPos) == p->getColour()) return false;
    } else {
        char currC = p->getPosition().first;
        int currI = p->getPosition().second;
        // check all square in between
        // Determine movement direction
        int colDiff = cPos - currC;
        int rowDiff = iPos - currI;
        int colStep = (colDiff == 0) ? 0 : (colDiff > 0) ? 1 : -1;
        int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0) ? 1 : -1;

        //make sure all squares inbetween are unoccupied
        char currentCol = currC;  // Start with the next position
        int currentRow = currI ;

        while (currentCol != cPos || currentRow != iPos) {
            currentCol += colStep;
            currentRow += rowStep;
            // cout << currentCol << currentRow << "\t" << occupied(currentCol, currentRow) << endl;
            if (occupied(currentCol, currentRow) == p->getColour()) return false;
            if ((p->getType() == 'P' || p->getType() == 'p') && colDiff != 0 && occupied(currentCol, currentRow) == NULL_C) return false;

        }

    }
    if(simulateAttack2(p, cPos, iPos)) return false;
    // run in check simulation
    if(p->getType() == 'K' || p->getType() == 'k') {
        if (canCastle(p->getColour())) {
            if (p->getColour() == WHITE && cPos == 'g' && iPos == 1) { 
                return true;
            } else if (p->getColour() == BLACK && cPos == 'g' && iPos == 8)  {
                return true;
            }
            else return false;
        }
    }
    return true;
}

bool BoardDisplay::simulateAttack2(Piece* p, char newC, int newI, Piece* checkAttack) {
    pair<char, int> currentPosition = p->getPosition();
    bool canBeAttacked = false;

    Piece* tempCapture = getBoardInfo(newC, newI);
    setState(p, newC, newI);
    setState(nullptr, currentPosition.first, currentPosition.second);

    PlayerInfo* currentPlayer = (p->getColour() == BLACK) ? blackPlayer : whitePlayer;
    PlayerInfo* oppositePlayer = (p->getColour() == BLACK) ? whitePlayer : blackPlayer;

    bool originalCheckState = currentPlayer->inCheck;
    currentPlayer->inCheck = false;

    for(const auto& piece : oppositePlayer->activePieces) {
        if (checkAttack) {
            canBeAttacked = checkValid(piece, checkAttack->getPosition().first, checkAttack->getPosition().second);
        } else {
            canBeAttacked = checkValid(piece, currentPlayer->kingPosition.first, currentPlayer->kingPosition.second);
        }
        if(canBeAttacked) break;
    }

    currentPlayer->inCheck = originalCheckState;
    
    setState(tempCapture, newC, newI);
    setState(p, currentPosition.first, currentPosition.second);

    return canBeAttacked;
}

std::pair<char, int> BoardDisplay::findPair(const std::vector<std::pair<char, int>>& vec, char cPos, int iPos) {
    for (const auto& pair : vec) {
        // cout << pair.first << pair.second << endl;
        if (pair.first == cPos && pair.second == iPos) {
            return pair;
        }
    }
    return {'i', 0};
}