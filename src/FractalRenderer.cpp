#include "FractalRenderer.hpp"

#include <iostream>

GLfloat FractalRenderer::m_device_verticies_carray[] = {
    -1.0f, -1.0f, // Bottom left
    -1.0f, 1.0f,  // Top left
    1.0f,  1.0f,
    1.0f, -1.0f
};

GLuint FractalRenderer::m_index_carray[] = {
    0,1,2,
    2,3,0
};

FractalRenderer::FractalRenderer(Settings &settings)
    : m_settings(settings)
    , m_current_fractal(Mandelbrot(m_settings))
    , m_vertex_buffer_layout()
    , m_vertex_buffer(sizeof(m_device_verticies_carray), m_device_verticies_carray, GL_DYNAMIC_DRAW)
    , m_vertex_array()
    , m_index_buffer(m_index_carray, 6, GL_DYNAMIC_DRAW)
{
    m_vertex_buffer_layout.PushBack(GL_FLOAT, 2);
    m_vertex_array.AddBuffer(m_vertex_buffer, m_vertex_buffer_layout);

    m_vertex_array.Bind();
    m_index_buffer.Bind();
    m_current_fractal.Bind();
}

FractalRenderer::~FractalRenderer()
{
    m_current_fractal.Destroy();
}

void FractalRenderer::SelectFractal(FractalType type)
{

    switch (type)
    {
        case FractalType::Mandel : m_current_fractal = Mandelbrot(m_settings); break;
        default : {
            std::cout << "Unknown fractal type!" << std::endl;
            return;
        }
    }

    m_current_fractal.Destroy();
}

void FractalRenderer::Render()
{
    m_current_fractal.Update();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}