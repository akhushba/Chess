#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include "observer.h"
#include <iostream>

class BoardDisplay;

class TextDisplay : public Observer {
    BoardDisplay* display;
    std::ostream &out = std::cout;

    public:
        TextDisplay(BoardDisplay* display);
        ~TextDisplay() override;
        void notify() override;
};

#endif
