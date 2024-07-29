#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H

#include <iostream>
#include <memory>
#include "observer.h"

class Xwindow;
class BoardDisplay;

class GraphicsDisplay : public Observer {
    BoardDisplay* display;
    std::unique_ptr<Xwindow> xw;
    const int top = 0, bottom = 85, left = 0, right = 145;
    const int cellSize = 100;  // Set the size of each square

    public:
        GraphicsDisplay(BoardDisplay* display);
        ~GraphicsDisplay() override = default;
        void notify() override;
};

#endif
