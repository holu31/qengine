#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gl_init.h"
#include "mesh.h"

static uint32_t dr_vao;
static uint32_t dr_vbo;
static uint32_t dr_vbo_offset;

void gl_draw_init(void) {
    glGenVertexArrays(1, &dr_vao);
    glGenBuffers(1, &dr_vbo);

    dr_vbo_offset = 0;
}

void gl_push_mesh(mesh_t mesh) {
    glBindBuffer(GL_ARRAY_BUFFER, dr_vbo);

    size_t verts_sizeof = sizeof(vertex_t) * mesh.verts_count; 
    glBufferData(GL_ARRAY_BUFFER, verts_sizeof, mesh.verts, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gl_flush(void) {
    glBindVertexArray(dr_vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, dr_vbo);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(vertex_t),
        NULL
    );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}
