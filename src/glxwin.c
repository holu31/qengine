#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <X11/Xutil.h>

#include "glxwin_int.h"
#include "glxwin.h"
#include "gl/gl_main.h"

static int visual_attribs[] = {
    GLX_X_RENDERABLE,   True,
    GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
    GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
    GLX_RED_SIZE,       8,
    GLX_GREEN_SIZE,     8,
    GLX_BLUE_SIZE,      8,
    GLX_ALPHA_SIZE,     8,
    GLX_DEPTH_SIZE,     24,
    GLX_STENCIL_SIZE,   8,
    GLX_DOUBLEBUFFER,   True,
    None
};

// FIXME
int is_extension_supported(const char* extension) {
    const GLubyte *extensions = NULL;
    const GLubyte *start;
    GLubyte *where, *terminator;

    where = (GLubyte *) strchr(extension, ' ');
    if (where || *extension == '\0')
        return 0;
    extensions = glGetString(GL_EXTENSIONS);
    start = extensions;
    for (;;) {
        where = (GLubyte *) strstr((const char *) start, extension);
        if (!where)
            break;
        terminator = where + strlen(extension);
        if (where == start || *(where - 1) == ' ')
        if (*terminator == ' ' || *terminator == '\0')
            return 1;
        start = terminator;
    }
    return 0;
}

XVisualInfo* glx_create_visualinfo(glxwin_t* win) {
    int screen = DefaultScreen(win->dpy);

    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(win->dpy, screen, visual_attribs, &fbcount); 
    if (!fbc) {
        fprintf(stderr, "glx: failed to choose a framebuffer config\n");
        return NULL;
    }
    printf("found %d framebuffer configs\n", fbcount);

    int best_fbc_idx = -1, worst_fbc_idx = -1;
    int best_num_samp = -1, worst_num_samp = -1;
    
    for (int i = 0; i < fbcount; i++) {
        XVisualInfo* vi = glXGetVisualFromFBConfig(win->dpy, fbc[i]);
        if (vi) {
            int samp_buf, samples;
            glXGetFBConfigAttrib(win->dpy, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
            glXGetFBConfigAttrib(win->dpy, fbc[i], GLX_SAMPLES, &samples);

            if (best_fbc_idx < 0 || samp_buf && samples > best_num_samp) {
                best_fbc_idx = i, best_num_samp = samples;
            }
            if (worst_fbc_idx < 0 || !samp_buf || samples < worst_num_samp) {
                worst_fbc_idx = i, worst_num_samp = samples;
            }
        }
        XFree(vi);
    }

    GLXFBConfig best_fbc = fbc[best_fbc_idx];

    XVisualInfo* vi = glXGetVisualFromFBConfig(win->dpy, best_fbc);
    printf("visual info ID=0x%lx\n", vi->visualid);

    XFree(fbc);

    return vi;
}

GLXContext glx_create_context(glxwin_t* win, XVisualInfo* vi) {
    GLXContext ctx = glXCreateContext(win->dpy, vi, NULL, GL_TRUE);
    if (!ctx) {
        fprintf(stderr, "glx: cannot create context.\n");
        return 0;
    }

    return ctx;
}

glxwin_t* win_create(void) {
    glxwin_t* win = malloc(sizeof(glxwin_t));

    win->dpy = XOpenDisplay(NULL);
    Window root = XDefaultRootWindow(win->dpy);

    XVisualInfo* vi = glx_create_visualinfo(win);
    if (vi == NULL) {
        return NULL;
    }

    int attrib_mask = CWBackPixel | CWColormap | CWEventMask;
    XSetWindowAttributes attrib = {};
    attrib.colormap = XCreateColormap(win->dpy, root,
            vi->visual, AllocNone); 
    attrib.background_pixel = 0x000000;
    attrib.event_mask = StructureNotifyMask | KeyReleaseMask | ExposureMask;

    win->handle = XCreateWindow(
        win->dpy,
        root,
        0, 0, 800, 600, 0,
        vi->depth, 
        InputOutput, vi->visual,
        attrib_mask, &attrib
    );

    XMapWindow(win->dpy, win->handle);
    XFlush(win->dpy);
    
    win->ctx = glx_create_context(win, vi);
    if (!win->ctx) {
        return NULL;
    }

    glXMakeCurrent(win->dpy, win->handle, win->ctx);

    gl_init();

    XFree(vi);

    return win;
}

void win_swapbuffers(glxwin_t* win) {
    glXSwapBuffers(win->dpy, win->handle);
}

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
