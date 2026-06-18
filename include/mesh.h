#ifndef MESH_H
#define MESH_H

typedef struct {
    float pos[3];
} vertex_t;

typedef struct {
    vertex_t* verts;
    uint32_t vert_count;

    uint32_t* inds;
    uint32_t ind_count;
} mesh_t;

#endif // MESH_H
