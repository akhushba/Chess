#include "textdisplay.h"

TextDisplay::TextDisplay(BoardDisplay* display): display{display} {}

TextDisplay::~TextDisplay() {
    delete display;
}