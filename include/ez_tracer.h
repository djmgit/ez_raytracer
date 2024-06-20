#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    Vec3 origin;
    Vec3 direction;
    float t;
} ray;

typedef Vec3 Color3;

Vec3 add(Vec3 *veca, Vec3 *vecb) {
    return (Vec3){veca->x + vecb->x, veca->y + vecb->y, veca->z + vecb->z};
}

void addEquals(Vec3 *self, Vec3 *vec) {
    self->x += vec->x;
    self->y += vec->y;
    self->z += vec->z;
}

Vec3 negate(Vec3 *vec) {
    return (Vec3){-1 * vec->x, -1 * vec->y, -1 * vec->z};
}

void negateSelf(Vec3 *self) {
    self->x = -1 * self->x;
    self->y = -1 * self->y;
    self->z = -1 * self->z;
}

float squared(Vec3 *vec) {
    return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

float magnitude(Vec3 *vec) {
    return sqrt(squared(vec));
}

Vec3 constant_multiply(Vec3 *veca, float factor) {
    return (Vec3){veca->x * factor, veca->y * factor, veca->z * factor};
}

void constant_multiply_equals(Vec3 *self, float factor) {
    self->x *= factor;
    self->y *= factor;
    self->z *= factor;
}

float dot(Vec3 *veca, Vec3 *vecb) {
    return veca->x * vecb->x + veca->y * vecb->y + veca->z * vecb->z;
}

float cos_angle(Vec3 *veca, Vec3 *vecb) {
    return (float)(dot(veca, vecb) / (magnitude(veca) * magnitude(vecb)));
}

Vec3 get_ray_vec3(ray *r) {
    Vec3 origin = r->origin;
    Vec3 tTimesDirection = constant_multiply(&r->direction, r->t);
    return add(&origin, &tTimesDirection);
}

Vec3 sub(Vec3 *veca, Vec3 *vecb) {
    Vec3 negatedVec = negate(vecb);
    return add(veca, &negatedVec);
}
