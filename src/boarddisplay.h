#ifndef _BOARD_DISPLAY_H_
#define _BOARD_DISPLAY_H_

#include "subject.h"
#include "colour.h"
#include "piece.h"


class BoardDisplay: public Subject {
  struct BoardSegment {
    Colour colour;
    Piece* piece;
  };

  class PlayerInfo {
    public:
        int score;
        bool inCheck;
        bool customSetup;
        bool canCastle;
  };

  BoardSegment board[8][8];

  void initializeBoard();

  public:
    PlayerInfo whitePlayer;
    PlayerInfo blackPlayer;
    
    void attach(Observer *o) override;
    void detach(Observer *o) override;
    void notifyObservers() override;
    virtual char getState(int row, int col) const = 0;
    virtual ~BoardDisplay() = default;
};
#endif
