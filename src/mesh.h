#ifndef MESH_H
#define MESH_H

typedef struct {
    float pos[3];
} vertex_t;

typedef struct {
    vertex_t* verts;
    size_t verts_count;

    uint32_t* inds;
    size_t inds_count;
} mesh_t;

typedef struct {
    uint32_t vao;
    uint32_t vbo;
} gl_mesh_t;

mesh_t create_mesh(
    vertex_t verts[], size_t verts_count,
    uint32_t inds[], size_t inds_count
)

#endif // MESH_H
