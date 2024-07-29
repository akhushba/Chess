#ifndef _BOARD_DISPLAY_H_
#define _BOARD_DISPLAY_H_

#include <utility>
#include <string>
#include <algorithm>
#include <vector>

#include "subject.h"
#include "colour.h"

class Piece;
class Player;

using namespace std;

class BoardDisplay final : public Subject {
    bool customSetup;
    struct BoardSegment {
        Colour colour;
        Piece* piece;

        void setBegin();
        BoardSegment(Colour c);
        ~BoardSegment() = default;
    };

public:
    class PlayerInfo {
    public:
        Player* player;
        int score;
        const Colour colour;
        bool inCheck;
        std::pair<char, int> kingPosition;
        std::vector<Piece*> activePieces;
        std::vector<Piece*> inactivePieces;

        void reset();

        PlayerInfo(Colour c, char kingC, int kingI, std::string playerType);
        ~PlayerInfo() = default;
    };

    BoardSegment board[8][8];
    PlayerInfo* whitePlayer; 
    PlayerInfo* blackPlayer; 

    void init();
    Piece* getBoardInfo(char c, int i);
    Colour getCurrentTurn;

    // Observer pattern
    void attach(Observer* o) override;
    void detach(Observer* o) override;
    void notifyObservers() override;
    char getState(int row, int col) const;

    void addPiece(char type, string pos);
    void removePiece(string pos);

public:
    std::vector<std::string> messages;

    PlayerInfo* getWhitePlayer();

    PlayerInfo* getBlackPlayer();

    PlayerInfo* getCurrentPlayer();

    void addWhitePlayer(string playerType);

    void addBlackPlayer(string playerType);

    // for the chessboard
    bool simulateAttack(Piece*, char newC, int newI, Piece* reference = nullptr);
    void setState(Piece* p, char cPos, int iPos, char pawnPromote = '\0');
    void makeMove(Colour currentColour, string oldpos, string newpos);
    bool canCapture(Colour pieceColour, char cPos, int iPos);
    Colour occupied(char c, int i);
    bool simulateInCheck(Piece* p, char newC, int newI);
    bool canCastle(Colour c);

    bool inCheck(Colour c);
    bool inCheckmate(Colour c);
    bool inStalemate(Colour c);
    void resign(Colour c);
    void endGame();
    void endSession();
    void setUpGame();
    BoardDisplay();
    ~BoardDisplay() = default;
};

#endif
