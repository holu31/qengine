#ifndef GL_MAIN_H
#define GL_MAIN_H

#include <GL/glx.h>
#include <GL/glxext.h>

#define LOAD_GL(t, n) \
    n = (t)gl_get_addr(#n);

extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLUSEPROGRAMPROC glUseProgram;

int is_extension_supported(const char* ext);
void* gl_get_addr(const char* name);

int gl_init(void);

#endif // GL_MAIN_H
