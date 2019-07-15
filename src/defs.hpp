#ifndef DEFS_H
#define DEFS_H

#define GLEW_STATIC
#include <GL/glew.h>

struct Settings {
    struct {
        GLfloat x0;
        GLfloat x1;
        GLfloat y0;
        GLfloat y1;
    } window;
};

enum FractalType {
    Default = 0,
    Mandel = 1,
};

#endif // DEFS_H