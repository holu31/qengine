#ifndef GLXWIN_INT_H
#define GLXWIN_INT_H

#include <X11/Xlib.h>
#include <GL/glx.h>

struct glxwin {
    Display* dpy;
    Window handle; 
    GLXWindow drawable;
    XVisualInfo *vi;
    GLXContext ctx;
};

#endif // GLXWIN_INT_H
