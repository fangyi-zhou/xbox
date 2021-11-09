// Code reused from the following tutorial
// https://tronche.com/gui/x/xlib-tutorial/2nd-program-anatomy.html

#include <X11/Xlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
  Display *display = XOpenDisplay(NULL);
  if (!display) {
    return 1;
  }
  printf("%s", "Opened display\n");
  int blackColor = BlackPixel(display, DefaultScreen(display));
  int whiteColor = WhitePixel(display, DefaultScreen(display));
  Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 200, 100, 0, blackColor, blackColor);
  XSelectInput(display, w, StructureNotifyMask);
  XMapWindow(display, w);
  GC gc = XCreateGC(display, w, 0, NULL);
  XSetForeground(display, gc, whiteColor);
  for (;;) {
    XEvent e;
    XNextEvent(display, &e);
    if (e.type == MapNotify) {
      break;
    }
  }
  XDrawLine(display, w, gc, 10, 60, 180, 20);
  XFlush(display);
  sleep(10);
  return 0;
}
