#ifndef MATHLIB_H
#define MATHLIB_H

#define VEC3(x, y, z) (vec3_t){x, y, z}
#define VEC4(x, y, z, w) (vec3_t){x, y, z, w}

typedef struct {
    float x, y, z;
} vec3_t;

typedef struct {
    float x, y, z, w;
} vec4_t;

typedef struct {
    float cells[16];
} mat4_t;

#endif // MATHLIB_H
