#ifndef DEFS_H
#define DEFS_H

#define GLEW_STATIC
#include <GL/glew.h>

struct Settings {
    struct {
        GLint x0;
        GLint y0;
        GLint x1;
        GLint y1;
    } window;
};

#endif // DEFS_H