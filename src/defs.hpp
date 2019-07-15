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
    Default = 0,
    Mandel = 1,
};

#endif // DEFS_H