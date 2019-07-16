#include "Fractals.hpp"

Fractal::Fractal(Settings &settings)
    : Shader(s_default_vert, s_default_frag)
    , m_settings(&settings)
{
    Bind();
    InitUniforms();
    Unbind();
}

void Fractal::InitUniforms() {
    SetUniform1f("u_width", m_settings->window.resolution.width);
    SetUniform1f("u_height", m_settings->window.resolution.height);
    SetUniform1f("u_x0", m_settings->window.x0);
    SetUniform1f("u_y0", m_settings->window.y0);
    SetUniform1f("u_x", m_settings->window.x);
    SetUniform1f("u_y", m_settings->window.y);
}

void Fractal::Update() {
    SetUniform1f("u_width", m_settings->window.resolution.width);
    SetUniform1f("u_height", m_settings->window.resolution.height);
    SetUniform1f("u_x0", m_settings->window.x0);
    SetUniform1f("u_y0", m_settings->window.y0);
    SetUniform1f("u_x", m_settings->window.x);
    SetUniform1f("u_y", m_settings->window.y);
    UpdateFractal();
}

const char *Fractal::s_default_vert = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    
    out gl_PerVertex { vec4 gl_Position; };

    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

const char *Fractal::s_default_frag =  R"(
    #version 330 core
    out vec4 FragColor;

    uniform float u_width;
    uniform float u_height;
    uniform float u_x0;
    uniform float u_y0;
    uniform float u_x;
    uniform float u_y;
    
    void main()
    {
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    } 
)";

/////////////////////////////// Mandelbrot /////////////////////////////////////

Mandelbrot::Mandelbrot(Settings &settings)
    : Shader(s_vert, s_frag)
    , Fractal(settings)
{
}

const char *Mandelbrot::s_vert =  R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    out gl_PerVertex { vec4 gl_Position; };

    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

const char *Mandelbrot::s_frag = R"(
    #version 330 core
    
    #define PI 3.14159
    const int MAX_ITERATIONS = 100;

    out vec4 FragColor;

    uniform float u_width;
    uniform float u_height;
    uniform float u_x0;
    uniform float u_y0;
    uniform float u_x;
    uniform float u_y;

    float mandelbrot(in float x0, in float y0, out float iterations)
    {
        iterations = 0;

        float x = 0;
        float y = 0;

        while ((x*x + y*y <= 4) && (iterations < MAX_ITERATIONS))
        {
            float x_temp = x*x - y*y + x0;
            y = 2*x*y + y0;
            x = x_temp;
            iterations++;
        }

        if (iterations == MAX_ITERATIONS) {
            return iterations;
        }
        else {
            return iterations + 1 - log(log2(x*x + y*y));
        }
    
    }
    
    void main()
    {
        float x = u_x0 + u_x * (gl_FragCoord.x / u_width); 
        float y = u_y0 + u_y * (gl_FragCoord.y * u_height / 1080 / u_width);

        float iterations;
        mandelbrot(x, y, iterations);
        float normalised = iterations / MAX_ITERATIONS;

        FragColor = vec4(normalised, normalised, normalised, normalised);
    } 
)";