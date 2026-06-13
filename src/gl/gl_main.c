#include <stdio.h>

#include "gl_main.h"

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLUSEPROGRAMPROC glUseProgram;

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
    LOAD_GL(PFNGLUSEPROGRAMPROC, glUseProgram); 

    return 0;
}
