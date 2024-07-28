#ifndef _BOARD_DISPLAY_H_
#define _BOARD_DISPLAY_H_

#include <memory> // Include for unique_ptr
#include "subject.h"
#include "colour.h"
#include "piece.h"
#include <utility>
#include <vector>

class Piece;

class BoardDisplay final: public Subject {
public:
    struct BoardSegment {
        Colour colour;
        Piece* piece;

        BoardSegment(Colour c) : colour{c}, piece{nullptr} {}
        ~BoardSegment() = default;
    };

    class PlayerInfo {
    public:
        int score;
        const Colour colour;
        bool inCheck;
        bool customSetup;
        bool canCastle;
        std::pair<char, int> kingPosition;
        std::vector<std::unique_ptr<Piece>> activePieces;
        std::vector<std::unique_ptr<Piece>> inactivePieces;
        std::vector<std::unique_ptr<Piece>> deactivedPieces;

        PlayerInfo(Colour c, char kingC, int kingI)
            : score{0}, colour{c}, inCheck{false}, customSetup{false}, canCastle{true} {}
        ~PlayerInfo() = default;
    };

private:
    std::unique_ptr<BoardSegment> board[8][8]; 
    std::unique_ptr<PlayerInfo> whitePlayer; 
    std::unique_ptr<PlayerInfo> blackPlayer; 

    void init();
    BoardSegment* getBoardInfo(char c, int i);

public:
    std::vector<std::string> messages;

    // Observer pattern
    void attach(Observer *o) override;
    void detach(Observer *o) override;
    void notifyObservers() override;
    char getState(int row, int col) const;

    //for the chessboard
    bool simulateAttack(Piece*, char newC, int newI, Piece* reference = nullptr);
    void setState(Piece* p, char cPos, int iPos);
    bool canCapture(Colour pieceColour, char cPos, int iPos);
    Colour occupied(char c, int i);
    bool simulateInCheck(Piece* p, char newC, int newI);


    bool inCheck(Colour c);
    bool inCheckmate(Colour c);
    void resign();
    void endGame();
    void endSession();

    BoardDisplay();
    ~BoardDisplay() = default; 
};

#endif
