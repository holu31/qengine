#ifndef GLXWIN_H
#define GLXWIN_H

typedef struct glxwin glxwin_t;

glxwin_t* win_create(void);
void win_swapbuffers(glxwin_t* win);
void win_pollevents(glxwin_t* win);
void win_destroy(glxwin_t* win);

#endif // GLXWIN_H
