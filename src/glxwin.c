#include <stdlib.h>
#include <stdio.h>
#include <X11/Xutil.h>

#include "glxwin_int.h"
#include "glxwin.h"
#include "gl/gl_main.h"

static int visual_attribs[] = {
    GLX_X_RENDERABLE,   True,
    GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT
    GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
    None
};

void glx_create_context(glxwin_t* win) {
    win->ctx = glXCreateContext(win->dpy, win->vi, 0, GL_FALSE);
    if (!win->ctx) {
        fprintf(stderr, "glx: cannot create context.\n");
    }
}

glxwin_t* win_create(void) {
    glxwin_t* win = malloc(sizeof(glxwin_t));

    win->dpy = XOpenDisplay(NULL);
    Window root = XDefaultRootWindow(win->dpy);

    int attrib_mask = CWBackPixel | CWEventMask;
    XSetWindowAttributes attrib = {};
    attrib.background_pixel = 0x000000;
    attrib.event_mask = StructureNotifyMask | KeyReleaseMask | ExposureMask;
    
    win->handle = XCreateWindow(
        win->dpy,
        root,
        0, 0, 800, 600,
        0, 
        CopyFromParent, CopyFromParent, CopyFromParent,
        attrib_mask, &attrib
    );

    XMapWindow(win->dpy, win->handle);
    XFlush(win->dpy);
    
    gl_init();
    glx_create_context(win);

    glXMakeCurrent(win->dpy, win->handle, win->ctx);

    return win;
}

void win_swapbuffers(glxwin_t* win) {}

void win_waitevents(glxwin_t* win) {
    XEvent event = {};
    XNextEvent(win->dpy, &event);

    switch (event.type) {
        case KeyRelease: {
            XKeyReleasedEvent* keyevent = (XKeyReleasedEvent*)&event;
            break;
        }
        case ClientMessage: {

            break;                    
        }
    }
}

void win_destroy(glxwin_t* win) {
    glXMakeCurrent(win->dpy, win->handle, NULL);

    XDestroyWindow(win->dpy, win->handle);
    XCloseDisplay(win->dpy);
    free(win);
}
