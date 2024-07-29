#include "graphicsdisplay.h"
#include <memory>

#include "observer.h"
#include "boarddisplay.h"
#include "window.h"

GraphicsDisplay::GraphicsDisplay(BoardDisplay* display) 
    : display{display}, xw{std::make_unique<Xwindow>(1450, 850)} {
    
    int colour;

  // Assuming `w` is your Xwindow instance
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
    const int pixelSize = 1;  // Size of each pixel in the cell

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            // Loop through each pixel within the cell
            for (int y = 0; y < cellSize; ++y) {
                for (int x = 0; x < cellSize; ++x) {
                    char c = display->getState(row * cellSize + y, col * cellSize + x); // Get the state of the pixel

                    int colour;
                    switch (c) {
                        case '-':
                            colour = Xwindow::Cacao; // Cacao Brown
                            break;
                        case ' ':
                            colour = Xwindow::Sand;  // Sand Brown
                            break;
                        case '0':
                            colour = Xwindow::White; // White
                            break;
                        case '1':
                            colour = Xwindow::Black; // Black
                            break;
                        default:
                            colour = Xwindow::Sand;  // Default to Sand Brown if unknown state
                            break;
                    }

                    // Update the pixel in the graphics window
                    xw->fillRectangle(col * cellSize + x * pixelSize, row * cellSize + y * pixelSize, pixelSize, pixelSize, colour);
                }
            }
        }
    }
    xw->drawString(900, 100, "BOARD STATUS");
    int textOffset = 25;
    for(auto s : display->messages) {
        xw->drawString(900, 100 + textOffset, s);
        textOffset += 25;
    }
}
