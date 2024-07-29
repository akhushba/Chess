#ifndef _BOARD_DISPLAY_H_
#define _BOARD_DISPLAY_H_

#include <memory> // Include for unique_ptr
#include <utility>
#include <string>
#include <algorithm>
#include <vector>

#include "subject.h"
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

using namespace std;

class Piece;

class BoardDisplay final: public Subject {
    bool customSetup;
    struct BoardSegment {
        Colour colour;
        Piece* piece;

        void setBegin(){
            piece = nullptr;
        }
        BoardSegment(Colour c) : colour{c}, piece{nullptr} {}
        ~BoardSegment() = default;
      
    };
public:
    class PlayerInfo {
        public:
            std::unique_ptr<Player> player;
            int score;
            const Colour colour;
            bool inCheck;
            std::pair<char, int> kingPosition;
            std::vector<std::unique_ptr<Piece>> activePieces;
            std::vector<std::unique_ptr<Piece>> inactivePieces;

            PlayerInfo(Colour c, char kingC, int kingI, std::string playerType)
                : score{0}, colour{c}, inCheck{false} {
                    if(playerType == "human") {

                    } else if (playerType == "computer1") {

                    } else if (playerType == "computer2") {

                    } else if (playerType == "computer3") {

                    } else if (playerType == "computer4") {

                    } 
                }
            ~PlayerInfo() = default;
    };

    std::unique_ptr<BoardSegment> board[8][8]; 
    std::unique_ptr<PlayerInfo> whitePlayer; 
    std::unique_ptr<PlayerInfo> blackPlayer; 

    void init();
    BoardSegment* getBoardInfo(char c, int i);
    Colour getCurrentTurn;

    // Observer pattern
    void attach(Observer *o) override;
    void detach(Observer *o) override;
    void notifyObservers() override;
    char getState(int row, int col) const;

    void addPiece(char type, string pos);
    void removePiece(string pos);
public:
    std::vector<std::string> messages;
    PlayerInfo* getWhitePlayer() {
        return whitePlayer.get();
    }

    PlayerInfo* getBlackPlayer() {
        return blackPlayer.get();
    }
    PlayerInfo* getCurrentPlayer() {
        if(getCurrentTurn== WHITE){
            return whitePlayer.get();
        }
        if(getCurrentTurn== BLACK){
            return blackPlayer.get();
        }
    }

    void addWhitePlayer(string playerType) {
        whitePlayer = make_unique<PlayerInfo>(WHITE, 'e', 'f', playerType);
    }

    void addBlackPlayer(string playerType) {
        blackPlayer = make_unique<PlayerInfo>(BLACK, 'e', 'f', playerType);
        
    }

    //for the chessboard
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
