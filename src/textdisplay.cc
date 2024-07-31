#include "textdisplay.h"
#include "boarddisplay.h"

TextDisplay::TextDisplay(BoardDisplay* display): display{display} {
}

TextDisplay::~TextDisplay() {
}

void TextDisplay::notify() {
    const int SIZE = 8;
    //gets the board state for each square
    for (int i = SIZE - 1; i >= 0; --i) {
        //printing out the row identifiers
        out << (i + 1) << ' ';
        
        for (int j = 0; j < SIZE; ++j) {
            out << display->getState(i, j);

        }
        out << "\n";
    }
    //printing out the column identifers
    out << "  ";
    for (char c = 'a'; c < 'a' + SIZE; ++c) {
        out << c;
    }
    //printing out any messages
    out << "\n";
    out << "\nBOARD STATUS\n";
    out << "------------\n";
    out << display->message << "\n";

}
