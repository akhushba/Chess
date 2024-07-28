#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H

#include "observer.h"
#include "boarddisplay.h"
#include "window.h"
#include <iostream>

class GraphicsDisplay : public Observer {
    BoardDisplay* display;
    Xwindow xw;
    int top = 8, bottom = 8, left = 8, right = 8;

public:
    GraphicsDisplay(BoardDisplay* display);
    ~GraphicsDisplay() override;
    void notify() override;
};

#endif
