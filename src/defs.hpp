#ifndef DEFS_H
#define DEFS_H

#define GLEW_STATIC
#include <GL/glew.h>

struct Settings {
    struct {
        struct {
            GLfloat width;
            GLfloat height;
        } resolution;

        GLfloat x0;
        GLfloat y0;
        GLfloat x;
        GLfloat y;

    } window;
};

enum FractalType {
    DEFAULT = 0,
    MANDELBROT = 1,
    JULIA = 2
};

#endif // DEFS_H