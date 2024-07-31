#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

//essenitally the same as what we used in the assignment problems
class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=500, int height=500); 
  ~Xwindow();                            
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  enum {White=0, Black, Sand, Cacao}; // Available colours.

  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  void drawString(int x, int y, std::string msg);

};

#endif

