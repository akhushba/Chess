#ifndef _BOARD_DISPLAY_H_
#define _BOARD_DISPLAY_H_

#include "subject.h"
#include "colour.h"
#include "piece.h"
#include "chessboard.h"

// class BoardDisplay final;

class BoardDisplay final: public Subject {
  struct BoardSegment {
    Colour colour;
    Piece* piece;

    BoardSegment(Colour c): colour{c}, piece{nullptr} {}
  };

  class PlayerInfo {
    public:
      int score;
      const Colour colour;
      bool inCheck;
      bool customSetup;
      bool canCastle;
      pair<char, int> kingPosition;
      vector<Piece*> activePieces;
      vector<Piece*> inactivePieces;

      PlayerInfo(Colour c, char kingC, int kingI) : score{0}, colour{c}, inCheck{false}, customSetup{false}, canCastle{true} {}
  };

  BoardSegment* board[8][8];
  Chessboard* boardState;

  void initializeBoard();

  PlayerInfo* whitePlayer;
  PlayerInfo* blackPlayer;

  vector<string> messages;

  public:
    
    //observer pattern
    void attach(Observer *o) override;
    void detach(Observer *o) override;
    void notifyObservers() override;
    char getState(int row, int col) const;

    //for the chessboard
    bool simulateAttack(Piece*, char newC, int newI, Piece* reference = nullptr);
    void setState(Piece* p, char cPos, int iPos);
    bool canCapture(Colour pieceColour, char cPos, int iPos);
    void as(char cPos, int iPos, Piece* p);

    BoardDisplay(Chessboard* b, Colour c);
    ~BoardDisplay() = default;
};
#endif
