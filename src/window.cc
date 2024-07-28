#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0, (XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap = DefaultColormap(d, DefaultScreen(d));

  struct ColorDefinition {
    const char* name;
    int red;
    int green;
    int blue;
  };

  // Define the colors with RGB values.
  ColorDefinition colors[] = {
    {"white", 65535, 65535, 65535},  // White
    {"black", 0, 0, 0},              // Black
    {"sand brown", 53970, 46260, 35980},  // Sand Brown
    {"cacao brown", 35723, 17733, 4883}    // Cacao Brown
  };

  for(int i = 0; i < 4; ++i) {
    xcolour.red = colors[i].red;
    xcolour.green = colors[i].green;
    xcolour.blue = colors[i].blue;
    xcolour.flags = DoRed | DoGreen | DoBlue;

    if (!XAllocColor(d, cmap, &xcolour)) {
      cerr << "Failed to allocate color: " << colors[i].name << endl;
      exit(1);
    }
    colours[i] = xcolour.pixel;
  }

  XSetForeground(d, gc, colours[1]); // Set default color to black

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d, True);

  usleep(1000);

  // Make sure we don't race against the Window being shown
  XEvent ev;
  while(1) {
    XNextEvent(d, &ev);
    if(ev.type == Expose) break;
  }
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[1]); // Set back to black
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}
