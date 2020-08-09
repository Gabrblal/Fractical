#include "FractalRenderer.hpp"

#include <iostream>

GLfloat FractalRenderer::m_device_verticies_carray[] = {
    -1.0f, -1.0f, // Bottom left
    -1.0f, 1.0f,  // Top left
    1.0f,  1.0f,  // Top right
    1.0f, -1.0f   // Bottom right
};

GLuint FractalRenderer::m_index_carray[] = {
    0,1,2,
    2,3,0
};

FractalRenderer::FractalRenderer(Settings &settings)
    : m_settings(&settings)
    , m_current_fractal(Mandelbrot())
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
    m_current_fractal.InitFractal();
    m_current_fractal.SetWindowResolution(
        m_settings->window.resolution.width,
        m_settings->window.resolution.height
    );
}

FractalRenderer::~FractalRenderer()
{
    m_current_fractal.Destroy();
}

void FractalRenderer::SelectFractal(FractalType type)
{
    m_current_fractal.Destroy();

    switch (type)
    {
        case FractalType::MANDELBROT : m_current_fractal = Mandelbrot(); break;
        case FractalType::JULIA : m_current_fractal = Julia(); break;
        default : {
            std::cout << "Unknown fractal type!" << std::endl;
            return;
        }
    }

    m_current_fractal.Bind();
    m_current_fractal.InitFractal();
    m_current_fractal.SetWindowResolution(
        m_settings->window.resolution.width,
        m_settings->window.resolution.height
    );
}

void FractalRenderer::Render()
{
    m_current_fractal.SetWindowCoordinates(m_settings->window.x0, m_settings->window.y0);
    m_current_fractal.SetCartesianValues(m_settings->window.x, m_settings->window.y);
    m_current_fractal.UpdateFractal();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}