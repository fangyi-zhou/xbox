// Code reused from the following tutorial
// https://tronche.com/gui/x/xlib-tutorial/2nd-program-anatomy.html

#include <X11/Xlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define BOX_WIDTH 100
#define BOX_HEIGHT 100
#define BOX_INIT_X 35
#define BOX_INIT_Y 65
#define BOX_BG_DIFF_X 30
#define BOX_BG_DIFF_Y (-30)
#define X_MARK_DIFF 15
#define X_MARK_XSHIFT 4

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  Display *display = XOpenDisplay(NULL);
  if (!display) {
    perror("Cannot open display");
    return 1;
  }
  int blackColor = BlackPixel(display, DefaultScreen(display));
  int whiteColor = WhitePixel(display, DefaultScreen(display));
  Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 200,
                                 200, 0, blackColor, blackColor);
  Atom wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", True);
  XSetWMProtocols(display, w, &wm_delete, 1);
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
  // Draw the foreground box
  XDrawLine(display, w, gc, BOX_INIT_X, BOX_INIT_Y, BOX_INIT_X + BOX_WIDTH,
            BOX_INIT_Y);
  XDrawLine(display, w, gc, BOX_INIT_X, BOX_INIT_Y, BOX_INIT_X,
            BOX_INIT_Y + BOX_HEIGHT);
  XDrawLine(display, w, gc, BOX_INIT_X + BOX_WIDTH, BOX_INIT_Y,
            BOX_INIT_X + BOX_WIDTH, BOX_INIT_Y + BOX_HEIGHT);
  XDrawLine(display, w, gc, BOX_INIT_X, BOX_INIT_Y + BOX_HEIGHT,
            BOX_INIT_X + BOX_WIDTH, BOX_INIT_Y + BOX_HEIGHT);
  // Draw the background box
  XDrawLine(display, w, gc, BOX_INIT_X + BOX_BG_DIFF_X,
            BOX_INIT_Y + BOX_BG_DIFF_Y, BOX_INIT_X + BOX_WIDTH + BOX_BG_DIFF_X,
            BOX_INIT_Y + BOX_BG_DIFF_Y);
  XDrawLine(display, w, gc, BOX_INIT_X + BOX_WIDTH + BOX_BG_DIFF_X,
            BOX_INIT_Y + BOX_BG_DIFF_Y, BOX_INIT_X + BOX_WIDTH + BOX_BG_DIFF_X,
            BOX_INIT_Y + BOX_HEIGHT + BOX_BG_DIFF_Y);
  // Connect the foreground and background
  XDrawLine(display, w, gc, BOX_INIT_X, BOX_INIT_Y, BOX_INIT_X + BOX_BG_DIFF_X,
            BOX_INIT_Y + BOX_BG_DIFF_Y);
  XDrawLine(display, w, gc, BOX_INIT_X + BOX_WIDTH, BOX_INIT_Y,
            BOX_INIT_X + BOX_WIDTH + BOX_BG_DIFF_X, BOX_INIT_Y + BOX_BG_DIFF_Y);
  XDrawLine(display, w, gc, BOX_INIT_X + BOX_WIDTH, BOX_INIT_Y + BOX_HEIGHT,
            BOX_INIT_X + BOX_WIDTH + BOX_BG_DIFF_X,
            BOX_INIT_Y + BOX_HEIGHT + BOX_BG_DIFF_Y);
  // Draw an X on the front side
  // Add some hollow effect by shifting one of the stroke
  XDrawLine(display, w, gc, BOX_INIT_X + X_MARK_DIFF + X_MARK_XSHIFT,
            BOX_INIT_Y + X_MARK_DIFF,
            BOX_INIT_X + BOX_WIDTH - X_MARK_DIFF + X_MARK_XSHIFT,
            BOX_INIT_Y + BOX_HEIGHT - X_MARK_DIFF);
  XDrawLine(display, w, gc, BOX_INIT_X + X_MARK_DIFF - X_MARK_XSHIFT,
            BOX_INIT_Y + X_MARK_DIFF,
            BOX_INIT_X + BOX_WIDTH - X_MARK_DIFF - X_MARK_XSHIFT,
            BOX_INIT_Y + BOX_HEIGHT - X_MARK_DIFF);
  XDrawLine(display, w, gc, BOX_INIT_X + X_MARK_DIFF - X_MARK_XSHIFT,
            BOX_INIT_Y + X_MARK_DIFF, BOX_INIT_X + X_MARK_DIFF + X_MARK_XSHIFT,
            BOX_INIT_Y + X_MARK_DIFF);
  XDrawLine(display, w, gc,
            BOX_INIT_X + BOX_WIDTH - X_MARK_DIFF - X_MARK_XSHIFT,
            BOX_INIT_Y + BOX_HEIGHT - X_MARK_DIFF,
            BOX_INIT_X + BOX_WIDTH - X_MARK_DIFF + X_MARK_XSHIFT,
            BOX_INIT_Y + BOX_HEIGHT - X_MARK_DIFF);
  XDrawLine(display, w, gc, BOX_INIT_X + BOX_WIDTH - X_MARK_DIFF,
            BOX_INIT_Y + X_MARK_DIFF, BOX_INIT_X + X_MARK_DIFF,
            BOX_INIT_Y + BOX_HEIGHT - X_MARK_DIFF);
  XFlush(display);

  bool windowOpen = true;

  while (windowOpen) {
    XEvent ev;
    while (XPending(display) > 0) {
      XNextEvent(display, &ev);
      switch (ev.type) {
      case ClientMessage:
        XClientMessageEvent *e = (XClientMessageEvent *)&ev;
        if (e->data.l[0] == wm_delete)
          windowOpen = false;
        break;
      }
    }
  }
  return 0;
}
