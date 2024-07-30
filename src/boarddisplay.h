#ifndef _BOARD_DISPLAY_H_
#define _BOARD_DISPLAY_H_

#include <utility>
#include <string>
#include <algorithm>
#include <vector>

#include "subject.h"
#include "colour.h"
#include <optional>
class Piece;
class Player;

using namespace std;

class BoardDisplay final : public Subject {
public:
    bool customSetup;
    struct BoardSegment {
        Colour colour;
        Piece* piece;

        void setBegin();
        BoardSegment(Colour c);
        ~BoardSegment() = default;
    };

    class PlayerInfo {
    public:
        Player* player;
        int score;
        const Colour colour;
        bool inCheck;
        bool hasKing = false;
        pair<char, int> kingPosition;
        vector<Piece*> activePieces;
        vector<Piece*> inactivePieces;

        void reset();

        PlayerInfo(Colour c, char kingC, int kingI);
        ~PlayerInfo() = default;
    };

    BoardSegment* board[8][8];
    PlayerInfo* whitePlayer = nullptr; 
    PlayerInfo* blackPlayer = nullptr; 
    Colour getCurrentTurn = WHITE;

    void defaultBoard();
    Piece* getBoardInfo(char c, int i);

    // Observer pattern
    void attach(Observer* o) override;
    void notifyObservers() override;
    char getState(int row, int col) const;

    void addPiece(char type, string pos);
    void removePiece(char cPos, int iPos);

    std::vector<std::string> messages;

    PlayerInfo* getWhitePlayer();

    PlayerInfo* getBlackPlayer();

    PlayerInfo* getCurrentPlayer();

    bool simulateAttack(Piece*, char newC, int newI, Piece* reference = nullptr);
    void setState(Piece* p, char cPos, int iPos, bool tempState = false);
    void makeMove(Colour currentColour);
    bool canCapture(Colour pieceColour, char cPos, int iPos);
    Colour occupied(char c, int i);
    bool canCastle(Colour c);
    void setPlayers(string playerOne, string playerTwo);
    Player* setPlayer(Colour c, string playerType);

    bool inCheck(Colour c);
    bool inCheckmate(Colour c);
    bool inStalemate(Colour c);
    void resign(Colour c);
    void endGame();
    void endSession();
    void setUpGame();
    bool checkValid(Piece *p, char cPos, int iPos);
    vector<pair<char, int>> getValidMoves(Piece* p);
    BoardDisplay();
    ~BoardDisplay() = default;
std::pair<char, int> findPair(const std::vector<std::pair<char, int>>& vec, char cPos, int iPos);

};
#endif