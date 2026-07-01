#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gl_init.h"
#include "mesh.h"

#define MAX_VERTEX  1000000
#define MAX_INDEX   3000000
#define MAX_DCMD    10000

typedef struct {
    uint32_t inds_count;
    uint32_t insts_count;
    uint32_t first_idx;
    int32_t base_vertex;
    uint32_t base_inst;
} gl_dcmd_t;

typedef struct {
    uint32_t id;
    uint32_t offset;
} gl_buffer_t;

static uint32_t d_vao;
static gl_buffer_t d_vbo;
static gl_buffer_t d_ebo;
static uint32_t d_dib;

static gl_dcmd_t d_cmd_queue[MAX_DCMD];
static uint32_t d_mesh_count = 0;

void gl_buffer_init(gl_buffer_t* buf, GLenum target, size_t sz) {
    glGenBuffers(1, &buf->id);
    glBindBuffer(target, buf->id);
    glBufferData(target, sz, NULL, GL_DYNAMIC_DRAW);
    buf->offset = 0;
}

void gl_draw_init(void) {
    glGenVertexArrays(1, &d_vao);
    glBindVertexArray(d_vao);

    gl_buffer_init(&d_vbo, GL_ARRAY_BUFFER, MAX_VERTEX * sizeof(vertex_t));
    gl_buffer_init(&d_ebo, GL_ELEMENT_ARRAY_BUFFER, MAX_INDEX * sizeof(uint32_t));

    glGenBuffers(1, &d_dib);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, d_dib);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, MAX_DCMD * sizeof(gl_dcmd_t), NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, pos));

    glBindVertexArray(0);
}

void gl_push_mesh(mesh_t mesh) {
    size_t verts_size = sizeof(vertex_t) * mesh.verts_count;
    size_t inds_size = sizeof(uint32_t) * mesh.inds_count;

    int32_t base_vertex = (int32_t)(d_vbo.offset / sizeof(vertex_t));
    uint32_t first_idx = (uint32_t)(d_ebo.offset / sizeof(uint32_t)); 

    glBindBuffer(GL_ARRAY_BUFFER, d_vbo.id); 
    glBufferSubData(GL_ARRAY_BUFFER, d_vbo.offset, verts_size, mesh.verts); 
    d_vbo.offset += verts_size;


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d_ebo.id);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, d_ebo.offset, inds_size, mesh.inds); 
    d_ebo.offset += inds_size;

    d_cmd_queue[d_mesh_count].inds_count  = mesh.inds_count;
    d_cmd_queue[d_mesh_count].insts_count = 1;
    d_cmd_queue[d_mesh_count].first_idx   = first_idx;
    d_cmd_queue[d_mesh_count].base_vertex = base_vertex;
    d_cmd_queue[d_mesh_count].base_inst   = 0;

    d_mesh_count += 1;
}

void gl_flush(void) {
    if (d_mesh_count == 0) return;

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, d_dib);
    glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, d_mesh_count * sizeof(gl_dcmd_t), d_cmd_queue);

    glBindVertexArray(d_vao);

    glMultiDrawElementsIndirect(
        GL_TRIANGLES,
        GL_UNSIGNED_INT,
        NULL,
        d_mesh_count,
        0
    );

    glBindVertexArray(0);

    d_mesh_count = 0;
    d_vbo.offset = 0;
    d_ebo.offset = 0;
}
