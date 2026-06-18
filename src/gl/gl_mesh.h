#ifndef GL_MESH_H
#define GL_MESH_H

#include <stdint.h>

#include "mesh.h"

typedef struct {
    uint32_t vao; 
} gl_mesh_t;

gl_mesh_t* gl_create_mesh(mesh_t mesh);

#endif // GL_MESH_H
