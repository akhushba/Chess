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
        std::vector<Piece*> activePieces;
        std::vector<Piece*> inactivePieces;

        PlayerInfo(Colour c, char kingC, int kingI)
            : score{0}, colour{c}, inCheck{false}, customSetup{false}, canCastle{true} {}
        ~PlayerInfo() = default;
    };

private:
    std::unique_ptr<BoardSegment> board[8][8]; // Use unique_ptr for board segments
    std::unique_ptr<PlayerInfo> whitePlayer; // Use unique_ptr for PlayerInfo
    std::unique_ptr<PlayerInfo> blackPlayer; // Use unique_ptr for PlayerInfo

    void initializeBoard();

public:
    std::vector<std::string> messages;

    // Observer pattern
    void attach(Observer *o) override;
    void detach(Observer *o) override;
    void notifyObservers() override;
    char getState(int row, int col) const;

    // For the chessboard
    bool simulateInCheck(Piece* p, char newC, int newI);
    void setState(Piece* p, char cPos, int iPos);
    bool canCapture(Colour pieceColour, char cPos, int iPos);
    bool inCheck(Colour c);
    Colour occupied(char c, int i);

    BoardDisplay(Colour c);
    ~BoardDisplay() = default; 
};

#endif
