#include <stdio.h>
#include <string.h>

#include "gl_init.h"

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLBUFFERSUBDATAPROC glBufferSubData;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect;
PFNGLUSEPROGRAMPROC glUseProgram;

void* gl_get_addr(const char* name) {
    void* p = (void*)glXGetProcAddressARB((GLubyte*)name);
    if (!p) {
        fprintf(stderr, "failed to load %s\n", name);
    }

    return p;
}

void gl_init(void) {
    LOAD_GL(PFNGLCREATESHADERPROC, glCreateShader);
    LOAD_GL(PFNGLSHADERSOURCEPROC, glShaderSource);
    LOAD_GL(PFNGLCOMPILESHADERPROC, glCompileShader);
    LOAD_GL(PFNGLGENBUFFERSPROC, glGenBuffers);
    LOAD_GL(PFNGLBINDBUFFERPROC, glBindBuffer);
    LOAD_GL(PFNGLBUFFERDATAPROC, glBufferData);
    LOAD_GL(PFNGLBUFFERSUBDATAPROC, glBufferSubData);
    LOAD_GL(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    LOAD_GL(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
    LOAD_GL(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
    LOAD_GL(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);
    LOAD_GL(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);
    LOAD_GL(PFNGLMULTIDRAWELEMENTSINDIRECTPROC, glMultiDrawElementsIndirect);
    LOAD_GL(PFNGLUSEPROGRAMPROC, glUseProgram); 
}
