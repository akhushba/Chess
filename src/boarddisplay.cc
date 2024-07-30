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

BoardDisplay::~BoardDisplay() {

}

void BoardDisplay::BoardSegment::setBegin() {
    piece = nullptr;
}

BoardDisplay::PlayerInfo::PlayerInfo(Colour c, char kingC, int kingI)
    : player(nullptr), score{0}, colour{c}, inCheck{false}, kingPosition{kingC, kingI} {
}

void BoardDisplay::defaultBoard() {
    // White pieces
    addPiece('R', "a1");
    addPiece('B', "c1");
    addPiece('Q', "d1");
    addPiece('K', "e1");
    addPiece('B', "f1");
    addPiece('R', "h1");
    addPiece('N', "b1");
    addPiece('N', "g1");
    addPiece('P', "b2");
    addPiece('P', "a2");
    addPiece('P', "c2");
    addPiece('P', "d2");
    addPiece('P', "e2");
    addPiece('P', "f2");
    addPiece('P', "g2");
    addPiece('P', "h2");

    // Black pieces
    addPiece('r', "a8");
    addPiece('n', "b8");
    addPiece('b', "c8");
    addPiece('q', "d8");
    addPiece('k', "e8");
    addPiece('b', "f8");
    addPiece('n', "g8");
    addPiece('r', "h8");
    addPiece('p', "a7");
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
    return board[i - 1][c - 'a']->piece;
}

void BoardDisplay::attach(Observer* o) {
    Subject::attach(o);
}

void BoardDisplay::notifyObservers() {
    Subject::notifyObservers();
    message = "";
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
    int iPos = pos[1] - '0';

    // Check for valid board position
    if (iPos < 1 || iPos > 8 || cPos < 'a' || cPos > 'h') 
        throw std::runtime_error("Out of bounds position given");

    auto currPlayer = (c == BLACK) ? getBlackPlayer() : getWhitePlayer();
    std::unique_ptr<Piece> newPiece;

    // Create the new piece based on type
    switch (type) {
        case 'Q': case 'q': newPiece = std::make_unique<Queen>(c, cPos, iPos); break;
        case 'R': case 'r': newPiece = std::make_unique<Rook>(c, cPos, iPos); break;
        case 'B': case 'b': newPiece = std::make_unique<Bishop>(c, cPos, iPos); break;
        case 'N': case 'n': newPiece = std::make_unique<Knight>(c, cPos, iPos); break;
        case 'K': case 'k':
            if (currPlayer->hasKing) 
                throw std::runtime_error("Multiple kings are not allowed");
            newPiece = std::make_unique<King>(c, cPos, iPos);
            currPlayer->hasKing = true;
            break;
        case 'P': case 'p':
            if (iPos == 1 || iPos == 8) 
                throw std::runtime_error("Invalid pawn placement");
            newPiece = std::make_unique<Pawn>(c, cPos, iPos);
            break;
        default: throw std::runtime_error("Unrecognized piece type");
    }

    // Ensure no piece is currently at the position
    if (!getBoardInfo(cPos, iPos)) {
        currPlayer->activePieces.push_back(std::move(newPiece));
        board[iPos - 1][cPos - 'a']->piece = currPlayer->activePieces.back().get();
    } else {
        throw std::runtime_error("A piece already exists in this space, cannot add new piece");
    }
}

void BoardDisplay::removePiece(char cPos, int iPos) {
    Piece* p = getBoardInfo(cPos, iPos);

    if (p) {
        auto currentPlayer = (p->getColour() == BLACK) ? getBlackPlayer() : getWhitePlayer();
        auto& activePieces = currentPlayer->activePieces;

        // Find the piece in the activePieces vector
        auto it = std::find_if(activePieces.begin(), activePieces.end(),
            [p](const std::unique_ptr<Piece>& piece) { return piece.get() == p; });

        if (it != activePieces.end()) {
            activePieces.erase(it);
        }

        board[iPos - 1][cPos - 'a']->piece = nullptr;
    }
}

void BoardDisplay::setState(Piece* p, char cPos, int iPos, bool tempState) {
    if (p) {
        Colour col = p->getColour();
        auto currentPlayer = (col == BLACK) ? getBlackPlayer() : getWhitePlayer();

        if (p->getType() == 'K' || p->getType() == 'k') {
            currentPlayer->kingPosition = {cPos, iPos};
            if (canCastle(col) && std::abs(cPos - p->getPosition().first) == 2) {
                if (col == WHITE) {
                    setState(getBoardInfo('h', 1), 'f', 1, tempState);
                    setState(nullptr, 'h', 1, tempState);
                } else {
                    setState(getBoardInfo('h', 8), 'f', 8, tempState);
                    setState(nullptr, 'h', 8, tempState);
                }
            }
        } else if ((p->getType() == 'P' || p->getType() == 'p')) {
            if (((col == BLACK && iPos == 1) || (col == WHITE && iPos == 8)) && !tempState) {
                // Remove the pawn from activePieces
                auto& activePieces = currentPlayer->activePieces;
                auto it = std::find_if(activePieces.begin(), activePieces.end(),
                                       [p](const std::unique_ptr<Piece>& piece) { return piece.get() == p; });
                if (it != activePieces.end()) {
                    activePieces.erase(it);
                }

                char promotionType;
                if (std::cin >> promotionType) {
                    std::unique_ptr<Piece> promotedPiece;
                    switch (promotionType) {
                        case 'Q': case 'q': promotedPiece = std::make_unique<Queen>(col, cPos, iPos); break;
                        case 'R': case 'r': promotedPiece = std::make_unique<Rook>(col, cPos, iPos); break;
                        case 'B': case 'b': promotedPiece = std::make_unique<Bishop>(col, cPos, iPos); break;
                        case 'N': case 'n': promotedPiece = std::make_unique<Knight>(col, cPos, iPos); break;
                        default: throw std::runtime_error("Invalid pawn promotion type");
                    }
                    board[iPos - 1][cPos - 'a']->piece = promotedPiece.get();

                    currentPlayer->activePieces.push_back(std::move(promotedPiece));
                } else {
                    throw std::runtime_error("Expected pawn promotion");
                }
                return;
            }
        }

        if (canCapture(col, p->getPosition().first, p->getPosition().second) && !tempState) {
            removePiece(cPos, iPos);
        }

        p->setPos(cPos, iPos);
        p->hasMoved = true;
    }
    board[iPos - 1][cPos - 'a']->piece = p;
}

bool BoardDisplay::canCapture(Colour pieceColour, char cPos, int iPos) {
    Piece* piece = getBoardInfo(cPos, iPos);
    if (!piece) return false;
    else if (piece && piece->getColour() == pieceColour) return false;
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
    if (p) return p->getColour();
    return NULL_C;
}

bool BoardDisplay::inCheck(Colour c) {
    auto curr = (c == BLACK) ? getBlackPlayer() : getWhitePlayer();
    auto opp = (c == BLACK) ? getWhitePlayer() : getBlackPlayer();

    for (auto& p : opp->activePieces) {
        if (checkValid(p.get(), curr->kingPosition.first, curr->kingPosition.second)) {
            return true;
        }
    }
    return false;
}

bool BoardDisplay::inCheckmate(Colour c) {
    if (!inCheck(c)) return false;

    auto curr = (c == BLACK) ? getBlackPlayer() : getWhitePlayer();
    for (const auto& p : curr->activePieces) {
        if (!(getValidMoves(p.get()).empty())) return false;
    }
    return true;
}

bool BoardDisplay::inStalemate(Colour c) {
    if (inCheck(c)) return false;

    auto curr = (c == BLACK) ? getBlackPlayer() : getWhitePlayer();
    for (const auto& p : curr->activePieces) {
        if (!(getValidMoves(p.get()).empty())) return false;
    }
    return true;
}

void BoardDisplay::setUpGame() {
    std::string setupCommand;
    endGame();
    while (std::cin >> setupCommand) {
        if (setupCommand == "+") {
            char addnewPiece;
            std::string addPos;
            std::cin >> addnewPiece >> addPos;
            addPiece(addnewPiece, addPos);
        } else if (setupCommand == "-") {
            std::string removePos;
            std::cin >> removePos;
            removePiece(removePos[0], removePos[1] - '0');
        } else if (setupCommand == "=") {
            std::string colour;
            std::cin >> colour;
            getCurrentTurn = (colour == "WHITE") ? WHITE : BLACK;
        } else if (setupCommand == "done") {
            notifyObservers();
            customSetup = true;
            break;
        }
        notifyObservers();
    }
}

void BoardDisplay::resign(Colour c) {
    auto winningPlayer = (c == BLACK) ? getWhitePlayer() : getBlackPlayer();
    winningPlayer->score++;
    endGame();
    message = "CURRENT SCORE\n-------------\nWHITE: " 
            + std::to_string(getWhitePlayer()->score) 
            + "\nBLACK: " 
            + std::to_string(getBlackPlayer()->score);
    notifyObservers();
}

void BoardDisplay::PlayerInfo::reset() {
    inCheck = false;
    kingPosition = (colour == WHITE) ? std::make_pair('e', 1) : std::make_pair('e', 8);
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
    message = "FINAL SCORES\n-------------\nWHITE: " 
            + std::to_string(getWhitePlayer()->score) 
            + "\nBLACK: " 
            + std::to_string(getBlackPlayer()->score);

    notifyObservers();
}

std::vector<std::pair<char, int>> BoardDisplay::getValidMoves(Piece* p) {
    if (!p) return {};
    std::vector<std::pair<char, int>> validMoves;
    std::vector<std::pair<char, int>> moves = p->generate();

    for (auto m : moves) {
        if (p->getType() == 'N' || p->getType() == 'n') {
            if (occupied(m.first, m.second) == p->getColour()) continue;
        } else {
            char currC = p->getPosition().first;
            int currI = p->getPosition().second;

            int colDiff = m.first - currC;
            int rowDiff = m.second - currI;
            int colStep = (colDiff == 0) ? 0 : (colDiff > 0) ? 1 : -1;
            int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0) ? 1 : -1;

            char currentCol = currC;
            int currentRow = currI;

            while (currentCol != m.first || currentRow != m.second) {
                currentCol += colStep;
                currentRow += rowStep;

                if (occupied(currentCol, currentRow) == p->getColour()) goto checkMore;
                if ((p->getType() == 'P' || p->getType() == 'p') && colDiff != 0 && occupied(currentCol, currentRow) == NULL_C) goto checkMore;
            }
        }

        if (simulateAttack(p, m.first, m.second)) continue;
        if (p->getType() == 'K' || p->getType() == 'k') {
            if (canCastle(p->getColour())) {
                if (p->getColour() == WHITE && m.first == 'g' && m.second == 1) {
                    validMoves.emplace_back(m);
                    continue;
                } else if (p->getColour() == BLACK && m.first == 'g' && m.second == 8) {
                    validMoves.emplace_back(m);
                    continue;
                }
                else continue;
            }
        }
        validMoves.emplace_back(m);
    checkMore:
        continue;
    }
    return validMoves;
}

void BoardDisplay::makeMove(Colour c) {
    auto currentPlayer = (c == BLACK) ? getBlackPlayer() : getWhitePlayer();

    if (currentPlayer->player->getName() == "human") {
        std::string oldPos, newPos;
        std::cin >> oldPos >> newPos;
        Piece* p = getBoardInfo(oldPos[0], oldPos[1] - '0');

        if (checkValid(p, newPos[0], newPos[1] - '0')) {
            setState(p, newPos[0], newPos[1] - '0');
            setState(nullptr, oldPos[0], oldPos[1] - '0');
        } else throw std::runtime_error("Invalid move made");

    } else {
        auto otherPlayer = (c == BLACK) ? getWhitePlayer() : getBlackPlayer();
        std::vector<std::pair<Piece*, std::vector<std::pair<char, int>>>> pieceAndMoves;
        std::vector<std::pair<Piece*, std::vector<std::pair<char, int>>>> pieceAndCaptureMoves;
        std::vector<std::pair<Piece*, std::vector<std::pair<char, int>>>> opponentPieceAndMoves;
        std::vector<std::pair<char, int>> moves;
        std::vector<std::pair<char, int>> captureMoves;
        std::vector<std::pair<char, int>> opponentMoves;
        std::pair<Piece*, std::pair<char, int>> pieceMovePair;
        char prevType;
        std::pair<char, int> prevPosition;

        for (auto& active : currentPlayer->activePieces) {
            std::vector<std::pair<char, int>> gotMoves = getValidMoves(active.get());

            if (gotMoves.size() != 0) {
                char currentType = active.get()->getType();
                std::pair<char, int> currentPosition = active.get()->getPosition();

                if (currentType != prevType || currentPosition != prevPosition) {
                    pieceAndMoves.emplace_back(std::make_pair(active.get(), gotMoves));
                    prevType = currentType;
                    prevPosition = currentPosition;
                }
            }
            if (captureMoves.size() != 0) pieceAndCaptureMoves.emplace_back(std::make_pair(active.get(), captureMoves));
            moves.clear();
        }
        for (const auto& active : otherPlayer->activePieces) {
            for (auto pair : active->generate()) {
                if (checkValid(active.get(), std::get<0>(pair), std::get<1>(pair))) {
                    opponentMoves.emplace_back(std::make_pair(std::get<0>(pair), std::get<1>(pair)));
                }
            }
            if (opponentMoves.size() != 0) opponentPieceAndMoves.emplace_back(std::make_pair(active.get(), moves));
            opponentMoves.clear();
        }

        pieceMovePair = currentPlayer->player->move(pieceAndMoves, pieceAndCaptureMoves, opponentPieceAndMoves);

        Piece* movePiece = std::get<0>(pieceMovePair);
        char oldC = movePiece->getPosition().first;
        int oldI = movePiece->getPosition().second;
        char moveC = std::get<0>(std::get<1>(pieceMovePair));
        int moveI = std::get<1>(std::get<1>(pieceMovePair));

        setState(movePiece, moveC, moveI);
        setState(nullptr, oldC, oldI);
    }
    getCurrentTurn = (getCurrentTurn == BLACK) ? WHITE : BLACK;
    message = (getCurrentTurn == WHITE ? "White" : "Black") + std::string("'s Turn\n");
    notifyObservers();
}

BoardDisplay::PlayerInfo* BoardDisplay::getWhitePlayer() {
    return whitePlayer.get();
}

BoardDisplay::PlayerInfo* BoardDisplay::getBlackPlayer() {
    return blackPlayer.get();
}

BoardDisplay::PlayerInfo* BoardDisplay::getCurrentPlayer() {
    return getCurrentTurn == WHITE ? getWhitePlayer() : getBlackPlayer();
}

BoardDisplay::BoardDisplay() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Colour segmentColor = ((i + j) % 2 == 0) ? BLACK : WHITE;
            board[i][j] = std::make_unique<BoardSegment>(segmentColor);
        }
    }

    whitePlayer = std::make_unique<PlayerInfo>(Colour::WHITE, 'e', 1);
    blackPlayer = std::make_unique<PlayerInfo>(Colour::BLACK, 'e', 8);

    getCurrentTurn = WHITE;

    attach(new TextDisplay(this));
    // attach(new GraphicsDisplay(this));
    notifyObservers();
}

Player* BoardDisplay::setPlayer(Colour c, std::string playerType) {
    Player* p = (c == WHITE) ? getWhitePlayer()->player.get() : getBlackPlayer()->player.get();

    if (p) {
        if(c == WHITE) {
            getWhitePlayer()->player.reset();
        } else {
            getBlackPlayer()->player.reset();

        }
    }

    if (playerType == "human") {
        p = new Human("human", {}, c);
    } else if (playerType == "computer1") {
        p = new LevelOne("level one", {}, c);
    } else if (playerType == "computer2") {
        p = new LevelTwo("level two", {}, c);
    } else if (playerType == "computer3") {
        p = new LevelThree("level three", {}, c);
    } else if (playerType == "computer4") {
        p = new LevelFour("level four", {}, c);
    } else throw std::runtime_error("Invalid player type received");

    return p;
}

void BoardDisplay::setPlayers(std::string playerOne, std::string playerTwo) {
    whitePlayer->player.reset(setPlayer(WHITE, playerOne));
    blackPlayer->player.reset(setPlayer(BLACK, playerTwo));
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j]->setBegin();
        }
    }
    whitePlayer->activePieces.clear();
    blackPlayer->activePieces.clear();
    getCurrentTurn = WHITE;
}

bool BoardDisplay::checkValid(Piece* p, char cPos, int iPos) {
    if (!p) return false;
    std::vector<std::pair<char, int>> possible = p->generate();

    auto foundPair = findPair(possible, cPos, iPos);
    if (foundPair.first == 'i') {
        return false;
    }

    if (p->getType() == 'N' || p->getType() == 'n') {
        if (occupied(cPos, iPos) == p->getColour()) return false;
    } else {
        char currC = p->getPosition().first;
        int currI = p->getPosition().second;

        int colDiff = cPos - currC;
        int rowDiff = iPos - currI;
        int colStep = (colDiff == 0) ? 0 : (colDiff > 0) ? 1 : -1;
        int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0) ? 1 : -1;

        char currentCol = currC;
        int currentRow = currI;

        while (currentCol != cPos || currentRow != iPos) {
            currentCol += colStep;
            currentRow += rowStep;

            if (p->getType() == 'P' || p->getType() == 'p') {
                if (colDiff == 0 && occupied(currentCol, currentRow) != NULL_C) {
                    return false;
                } else if (colDiff != 0 && (occupied(currentCol, currentRow) == NULL_C || occupied(currentCol, currentRow) == p->getColour())) {
                    return false;
                } else if (colDiff > 0) return false;
            }

            if (occupied(currentCol, currentRow) == p->getColour()) return false;
        }
    }
    if (simulateAttack(p, cPos, iPos)) return false;
    if (p->getType() == 'K' || p->getType() == 'k') {
        if (canCastle(p->getColour())) {
            if (p->getColour() == WHITE && cPos == 'g' && iPos == 1) {
                return true;
            } else if (p->getColour() == BLACK && cPos == 'g' && iPos == 8) {
                return true;
            }
            else return false;
        }
    }
    return true;
}

bool BoardDisplay::simulateAttack(Piece* p, char newC, int newI, Piece* checkAttack) {
    std::pair<char, int> currentPosition = p->getPosition();
    bool canBeAttacked = false;

    Piece* tempCapture = getBoardInfo(newC, newI);
    setState(p, newC, newI, true);
    setState(nullptr, currentPosition.first, currentPosition.second, true);

    auto currentPlayer = (p->getColour() == BLACK) ? getBlackPlayer() : getWhitePlayer();
    auto oppositePlayer = (p->getColour() == BLACK) ? getWhitePlayer() : getBlackPlayer();

    bool originalCheckState = currentPlayer->inCheck;
    currentPlayer->inCheck = false;

    for (const auto& piece : oppositePlayer->activePieces) {
        if (checkAttack) {
            canBeAttacked = checkValid(piece.get(), checkAttack->getPosition().first, checkAttack->getPosition().second);
        } else {
            canBeAttacked = checkValid(piece.get(), currentPlayer->kingPosition.first, currentPlayer->kingPosition.second);
        }
        if (canBeAttacked) break;
    }

    currentPlayer->inCheck = originalCheckState;

    setState(tempCapture, newC, newI, true);
    setState(p, currentPosition.first, currentPosition.second, true);

    return canBeAttacked;
}

std::pair<char, int> BoardDisplay::findPair(const std::vector<std::pair<char, int>>& vec, char cPos, int iPos) {
    for (const auto& pair : vec) {
        if (pair.first == cPos && pair.second == iPos) {
            return pair;
        }
    }
    return { 'i', 0 };
}
