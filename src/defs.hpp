#ifndef DEFS_H
#define DEFS_H

#define GLEW_STATIC
#include <GL/glew.h>

struct Settings {
    struct {
        GLfloat x0;
        GLfloat y0;
        GLfloat x1;
        GLfloat y1;
    } window;
};

enum class FractalType {
    Default = 0,
    Mandelbrot = 1,
};

#endif // DEFS_H