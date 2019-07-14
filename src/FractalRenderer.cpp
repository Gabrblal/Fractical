#include "FractalRenderer.hpp"

#include <iostream>

GLfloat FractalRenderer::m_device_verticies_carray[] = {
    -0.5f, -0.5f,
    -0.5f, 0.5f,
    0.5f,  0.5f,
    0.5f, -0.5f
};

GLuint FractalRenderer::m_index_carray[] = {
    0,1,2,
    2,3,0
};

FractalRenderer::FractalRenderer(Settings &settings)
    : m_vertex_buffer(sizeof(m_device_verticies_carray), m_device_verticies_carray, GL_DYNAMIC_DRAW)
    , m_index_buffer(m_index_carray, 6, GL_DYNAMIC_DRAW)
    , m_settings(settings)
    , m_fractal_shader(Mandelbrot(m_settings))
{
    m_vertex_buffer_layout.PushBack(GL_FLOAT, 2);
    m_vertex_array.AddBuffer(m_vertex_buffer, m_vertex_buffer_layout);

    m_vertex_array.Bind();
    m_index_buffer.Bind();

    std::cout << "Binding in renderer is " << m_fractal_shader.m_id << std::endl;
    std::cout << "is program: " << (int)glIsProgram(m_fractal_shader.m_id) << std::endl;
    m_fractal_shader.Bind();
}

void FractalRenderer::SelectFractal(FractalType type)
{
    switch (type)
    {
        case FractalType::Mandelbrot : m_fractal_shader = Mandelbrot(m_settings); break;
        default : {
            std::cout << "Unknown fractal type!" << std::endl;
            return;
        }
    }

    m_fractal_shader.Bind();

}

void FractalRenderer::Render()
{
    m_fractal_shader.Update();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}