#include <stdio.h>
#include <stddef.h>
#include <GL/glx.h>

#include "glxwin.h"

int main(void) {
    glxwin_t* win = win_create();
    if (win == NULL) {
        fprintf(stderr, "main: failed to create win\n");
        return -1;
    }

    for (;;) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.f, 0.f, 0.f, 1.f);

        win_pollevents(win);
        win_swapbuffers(win);
    }

    win_destroy(win);

    return 0;
}
