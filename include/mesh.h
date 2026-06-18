#ifndef MESH_H
#define MESH_H

typedef struct {
    float v[3];
    int index;
} vertex_t;

typedef struct {
    vertex_t* verts;    
} mesh_t;

#endif // MESH_H
