#include "textdisplay.h"

TextDisplay::TextDisplay(BoardDisplay* display): display{display} {}

TextDisplay::~TextDisplay() {
    delete display;
}

void TextDisplay::notify() {
    const int SIZE = 8;

    // modify for specific character
    for (int i = SIZE - 1; i >= 0; --i) {
        out << (i + 1) << ' ';
        bool startWithUnderscore = (i % 2 == 0);
        
        for (int j = 0; j < SIZE; ++j) {
            if ((j % 2 == 0) == startWithUnderscore) {
                out << "_";
            } else {
                out << " ";
            }
        }
        out << "\n";
    }

    out << ' ';
    for (char c = 'a'; c < 'a' + SIZE; ++c) {
        out << c;
    }
    out << "\n";

}