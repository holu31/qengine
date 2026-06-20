#include <stdlib.h>
#include <GL/gl.h>

#include "mesh.h"
#include "gl_init.h"

mesh_t create_mesh(
    vertex_t verts[], size_t verts_count,
    uint32_t inds[], size_t inds_count
) { 
    mesh->verts_count = verts_count;
    mesh->verts = malloc(sizeof(vertex_t) * mesh->verts_count);
    if (mesh->verts == NULL) goto verts_clean;
    memcpy(mesh->verts, verts);

    mesh->inds_count = inds_count;
    mesh->inds = malloc(sizeof(uint32_t) * mesh->inds_count);
    if (mesh->inds == NULL) goto inds_clean;
    memcpy(mesh->inds, inds);

    return mesh;

inds_clean:
    free(mesh->verts);
verts_clean:
    return (mesh_t){0};
}
