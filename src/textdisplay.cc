#include "textdisplay.h"

// #include "boarddisplay.h"

TextDisplay::TextDisplay(BoardDisplay* display): display{display} {}

TextDisplay::~TextDisplay() {
    delete display;
}

void TextDisplay::notify() {
    const int SIZE = 8;

    for (int i = SIZE - 1; i >= 0; --i) {
        out << (i + 1) << ' ';
        
        for (int j = 0; j < SIZE; ++j) {
            // display->getState(i, j);
        }
        out << "\n";
    }

    out << ' ';
    for (char c = 'a'; c < 'a' + SIZE; ++c) {
        out << c;
    }
    out << "\n";

    // for(auto s : display->messages) out << s << "\n";

}