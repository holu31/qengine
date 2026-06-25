#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <GL/glx.h>

#include "gl_init.h"
#include "mesh.h"
#include "mathlib.h"

void gl_draw_init(void);
void gl_push_mesh(mesh_t mesh);
void gl_flush(void);

void cl_main(void) {
    mesh_t mesh;
    mesh.verts_count = 3;
    mesh.verts = malloc(sizeof(vertex_t) * 3);
    if (mesh.verts == NULL) {
        fprintf(stderr, "failed\n");
        return;
    } 

    mesh.verts[0].pos[0] = -1.0f;
    mesh.verts[0].pos[1] = -1.0f;
    mesh.verts[0].pos[2] = 0.0f;

    mesh.verts[1].pos[0] = 1.0f;
    mesh.verts[1].pos[1] = -1.0f;
    mesh.verts[1].pos[2] = 0.0f;

    mesh.verts[2].pos[0] = 0.0f;
    mesh.verts[2].pos[1] = 1.0f;
    mesh.verts[2].pos[2] = 0.0f;

    gl_push_mesh(mesh);
}

void cl_loop(void) {
    gl_flush();
}

#ifdef __linux__

#include <X11/Xutil.h>

Display* dpy;
Window handle; 
GLXContext ctx;

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

XVisualInfo* glx_create_visualinfo(void) {
    int screen = DefaultScreen(dpy);

    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(dpy, screen, visual_attribs, &fbcount); 
    if (!fbc) {
        fprintf(stderr, "glx: failed to choose a framebuffer config\n");
        return NULL;
    }
    printf("glx: found %d framebuffer configs\n", fbcount);

    int best_fbc_idx = -1;
    int best_num_samp = -1;
    
    for (int i = 0; i < fbcount; i++) {
        XVisualInfo* vi = glXGetVisualFromFBConfig(dpy, fbc[i]);
        if (vi) {
            int samp_buf, samples;
            glXGetFBConfigAttrib(dpy, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
            glXGetFBConfigAttrib(dpy, fbc[i], GLX_SAMPLES, &samples);

            if (best_fbc_idx < 0 || (samp_buf && samples > best_num_samp)) {
                best_fbc_idx = i, best_num_samp = samples;
            } 
        }
        XFree(vi);
    }

    GLXFBConfig best_fbc = fbc[best_fbc_idx];

    XVisualInfo* vi = glXGetVisualFromFBConfig(dpy, best_fbc);
    printf("glx: visual info ID=0x%lx\n", vi->visualid);

    XFree(fbc);

    return vi;
}

GLXContext glx_create_context(XVisualInfo* vi) {
    GLXContext ctx = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    if (!ctx) {
        fprintf(stderr, "glx: cannot create context.\n");
        return NULL;
    }

    return ctx;
}

int glx_win_create(void) {
    dpy = XOpenDisplay(NULL);
    Window root = XDefaultRootWindow(dpy);

    XVisualInfo* vi = glx_create_visualinfo();
    if (vi == NULL)
        return -1;

    int attrib_mask = CWBackPixel | CWColormap | CWEventMask;
    XSetWindowAttributes attrib = {};
    attrib.colormap = XCreateColormap(dpy, root,
            vi->visual, AllocNone); 
    attrib.background_pixel = 0x000000;
    attrib.event_mask = StructureNotifyMask | KeyReleaseMask | ExposureMask;

    handle = XCreateWindow(
        dpy,
        root,
        0, 0, 800, 600, 0,
        vi->depth, 
        InputOutput, vi->visual,
        attrib_mask, &attrib
    );

    XMapWindow(dpy, handle);
    XFlush(dpy);
    
    ctx = glx_create_context(vi);
    if (!ctx)
        return -1;

    glXMakeCurrent(dpy, handle, ctx);

    XFree(vi);

    return 0;
}

void glx_pollevents(void) {
    XPending(dpy);

    while (QLength(dpy)) {
        XEvent event = {};
        XNextEvent(dpy, &event);

        XFlush(dpy);
    }
}

int main(void) {
    if (glx_win_create() != 0) {
        fprintf(stderr, "main: failed to create win\n");
        return 1;
    }
    gl_init();
    gl_draw_init();

    cl_main();

    for (;;) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.f, 1.f);

        cl_loop();

        glx_pollevents();
        glXSwapBuffers(dpy, handle);
    }

    glXMakeCurrent(dpy, handle, NULL);

    XDestroyWindow(dpy, handle);
    XCloseDisplay(dpy);

    return 0;
}
#endif
