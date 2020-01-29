#pragma once
/**
 * Vectors
 */
typedef struct {
    union { float left  , r, x0; };
    union { float top   , g, y0; };
    union { float right , b, x1; };
    union { float bottom, a, y1; };
} Vec4f;

typedef struct {
    union { int left  , r, x0; };
    union { int top   , g, y0; };
    union { int right , b, x1; };
    union { int bottom, a, y1; };
} Vec4i;

typedef struct {
    union { int x, a; };
    union { int y, b; };
} Vec2i;
