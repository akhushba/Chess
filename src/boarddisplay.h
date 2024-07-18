#ifndef _BOARD_DISPLAY_H_
#define _BOARD_DISPLAY_H_

#include "subject.h"

class BoardDisplay: public Subject {
public:
  void attach(Observer *o) override;
  void detach(Observer *o) override;
  void notifyObservers() override;
  virtual char getState(int row, int col) const = 0;
  virtual ~BoardDisplay() = default;
};
#endif
