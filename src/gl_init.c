#include <stdio.h>
#include <string.h>

#include "gl_init.h"

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLUSEPROGRAMPROC glUseProgram;

int is_extension_supported(const char* ext) {
    const GLubyte* exts = NULL;
    const GLubyte* start;
    GLubyte* where, *term;

    where = (GLubyte*)strchr(ext, ' ');
    if (where || *ext == '\0')
       return 0;
    exts = glGetString(GL_EXTENSIONS);
    start = exts;
    for (;;) {
        where = (GLubyte*)strstr((const char*)start, ext);
        if (!where)
            break;
        term = where + strlen(ext);
        if (where == start || *(where - 1) == ' ')
        if (*term == ' ' || *term == '\0')
            return 1;
        start = term;
    }
    return 0;
}

void* gl_get_addr(const char* name) {
    void* p = (void*)glXGetProcAddressARB((GLubyte*)name);
    if (!p) {
        fprintf(stderr, "failed to load %s\n", name);
    }

    return p;
}

int gl_init(void) {
    LOAD_GL(PFNGLCREATESHADERPROC, glCreateShader);
    LOAD_GL(PFNGLSHADERSOURCEPROC, glShaderSource);
    LOAD_GL(PFNGLCOMPILESHADERPROC, glCompileShader);
    LOAD_GL(PFNGLGENBUFFERSPROC, glGenBuffers);
    LOAD_GL(PFNGLBINDBUFFERPROC, glBindBuffer);
    LOAD_GL(PFNGLBUFFERDATAPROC, glBufferData);
    LOAD_GL(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    LOAD_GL(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
    LOAD_GL(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
    LOAD_GL(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
    LOAD_GL(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
    LOAD_GL(PFNGLUSEPROGRAMPROC, glUseProgram); 

    return 0;
}
