#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include "observer.h"
#include "boarddisplay.h"
#include <iostream>

class TextDisplay : public Observer {
    BoardDisplay* display;
    int top = 8, bottom = 8, left  = 8, right  = 8;
    std::ostream &out = std::cout;

public:
    TextDisplay(BoardDisplay* display);
    ~TextDisplay();
    void notify() override;
};

#endif
