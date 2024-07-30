#include "graphicsdisplay.h"
#include <memory>
#include "boarddisplay.h"
#include "window.h"
#include <exception>
#include <iostream>
#include <string>
#include "array.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(BoardDisplay* display) 
    : display{display}, xw{std::make_unique<Xwindow>(1450, 850)} {
    
    int colour;

    // Draw initial board background
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            char c = display->getState(row, col);
            colour = c == '-' ? Xwindow::Cacao : Xwindow::Sand;
            xw->fillRectangle(col * cellSize, row * cellSize, cellSize, cellSize, colour);
        }
    }
}

void GraphicsDisplay::notify() {
    const int cellSize = 100; // Size of each cell

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Reverse the color for correct board orientation
            int colour = ((row + col) % 2 == 0) ? Xwindow::Cacao : Xwindow::Sand;
            char type = display->getState(row, col);

            // Fill the cell with the determined background color
            xw->fillRectangle(col * cellSize, (7 - row) * cellSize, cellSize, cellSize, colour);

            // Determine the piece artwork
            const std::array<std::array<char, 25>, 25>& art = 
                (type == 'Q' || type == 'q') ? QUEEN :
                (type == 'R' || type == 'r') ? ROOK :
                (type == 'B' || type == 'b') ? BISHOP :
                (type == 'N' || type == 'n') ? KNIGHT :
                (type == 'K' || type == 'k') ? KING :
                (type == 'P' || type == 'p') ? PAWN :
                std::array<std::array<char, 25>, 25>{}; 

            bool isBlack = (type < 'z' && type > 'a' );
            int pixelColour = colour;
            if (art != std::array<std::array<char, 25>, 25>{}) {
                // Loop through each pixel in the 25x25 art array
                for (int y = 0; y < 25; ++y) {
                    for (int x = 0; x < 25; ++x) {
                        // Determine the color based on the art array value
                        if(isBlack && art[y][x] == '0') pixelColour = Xwindow::Black;
                        else if(art[y][x] == '1') pixelColour = Xwindow::Black;
                        else pixelColour = colour;
                        // Draw a 4x4 block for each pixel
                        xw->fillRectangle(col * cellSize + x * 4, (7 - row) * cellSize + y * 4, 4, 4, pixelColour);
                    }
                }
            }
        }
    }

    xw->drawString(900, 100, "BOARD STATUS");
    int textOffset = 25;
    for (auto s : display->messages) {
        xw->drawString(900, 100 + textOffset, s);
        textOffset += 25;
    }
}
