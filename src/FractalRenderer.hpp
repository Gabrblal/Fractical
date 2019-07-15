#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "defs.hpp"
#include "Vertex.hpp"
#include "Shader.hpp"

#include <unordered_map>
#include <memory>

class FractalRenderer
{
    static GLfloat m_device_verticies_carray[];
    static GLuint m_index_carray[];

    // Redefining a single fractal reference is not possible since temporaries
    // call the destructure that deletes the shader on the GPU side.

    public:
        FractalRenderer(Settings &settings);
        ~FractalRenderer();

        void SelectFractal(FractalType type);
        void Render();

    private:
        Settings m_settings;
        Fractal m_current_fractal;

        VertexBufferLayout m_vertex_buffer_layout;
        VertexBuffer m_vertex_buffer;
        VertexArray m_vertex_array;
        IndexBuffer m_index_buffer;

};

#endif // RENDERER_H