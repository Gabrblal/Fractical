#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include "GL/glew.h"

#include "defs.hpp"
#include "Vertex.hpp"
#include "Fractals.hpp"

#include <unordered_map>

// Handles rendering the various fractals defined in Fractals.cpp
class FractalRenderer
{
    static GLfloat m_device_verticies_carray[];
    static GLuint m_index_carray[];

    public:
        FractalRenderer(Settings &settings);
        ~FractalRenderer();

        void SelectFractal(FractalType type);
        void Render();

    private:
        Settings* m_settings;
        Fractal m_current_fractal;

        VertexBufferLayout m_vertex_buffer_layout;
        VertexBuffer m_vertex_buffer;
        VertexArray m_vertex_array;
        IndexBuffer m_index_buffer;

};

#endif // RENDERER_H