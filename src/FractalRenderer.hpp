#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "defs.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"

class FractalRenderer
{
    static GLfloat m_device_verticies_carray[];
    static GLuint m_index_carray[];

    public:
        FractalRenderer(Settings &settings);

        void SelectFractal(FractalType type);
        void Render();

    private:
        Settings m_settings;

        VertexBufferLayout m_vertex_buffer_layout;
        VertexBuffer m_vertex_buffer;
        VertexArray m_vertex_array;
        IndexBuffer m_index_buffer;

        Fractal m_fractal_shader;

};

#endif // RENDERER_H