#include "Fractals.hpp"

Fractal::Fractal()
    : Shader(s_default_vert, s_default_frag)
{
    Bind();
    SetWindowResolution(s_default_settings.width, s_default_settings.height);
    SetWindowCoordinates(s_default_settings.x0, s_default_settings.y0);
    SetCartesianValues(s_default_settings.x, s_default_settings.y);
    Unbind();
}

void Fractal::SetWindowResolution(GLfloat width, GLfloat height)
{
    SetUniform1f("u_width", width);
    SetUniform1f("u_height", height);
}

void Fractal::SetWindowCoordinates(GLfloat x0, GLfloat y0)
{
    SetUniform1f("u_x0", x0);
    SetUniform1f("u_y0", y0);
}

void Fractal::SetCartesianValues(GLfloat x, GLfloat y)
{
    SetUniform1f("u_x", x);
    SetUniform1f("u_y", y);
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

Mandelbrot::Mandelbrot()
    : Shader(s_vert, s_frag)
    , Fractal()
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

        float rsquare = 0;
        float isquare = 0;
        float zsquare = 0;

        // https://en.wikipedia.org/wiki/Mandelbrot_set#Escape_time_algorithm
        
        while ((rsquare + isquare <= 4) && (iterations < MAX_ITERATIONS))
        {
            x = rsquare - isquare + x0;
            y = zsquare - rsquare - isquare + y0;
            rsquare = x*x;
            isquare = y*y;
            zsquare = (x + y) * (x + y);
            iterations++;
        }

        // TODO: Implement Multibrots
        // while ((x*x + y*y <= 4) && (iterations < MAX_ITERATIONS))
        // {
        //     float xtemp = pow( (x*x + y*y), u_n/2) * cos(u_n * pow(atan(y, x), 2)) + x0;
        //     y = pow( (x*x + y*y), u_n/2) * sin(u_n * pow(atan(y, x), 2)) + y0;
        //     x = xtemp;
        //     iterations++;
        // }

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
        float y = u_y0 + u_y * (gl_FragCoord.y / u_width);

        float iterations;
        mandelbrot(x, y, iterations);
        float normalised = iterations / MAX_ITERATIONS;

        FragColor = vec4(normalised, normalised, normalised, normalised);
    } 
)";

Julia::Julia()
    : Shader(s_vert, s_frag)
    , Fractal()
{
}

void Julia::InitFractal()
{
    SetUniform1f("u_cx", 0.0);
    SetUniform1f("u_cy", 1.0);
}

void Julia::UpdateFractal()
{

}

const char *Julia::s_vert =  R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    out gl_PerVertex { vec4 gl_Position; };

    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

const char *Julia::s_frag = R"(
     #version 330 core
    
    const int MAX_ITERATIONS = 100;

    out vec4 FragColor;

    uniform float u_width;
    uniform float u_height;
    uniform float u_x0;
    uniform float u_y0;
    uniform float u_x;
    uniform float u_y;

    uniform float u_cx;
    uniform float u_cy;

    float julia(in float x0, in float y0, out float iterations)
    {
        iterations = 0;
        float x = x0;
        float y = y0;

        while ((x*x + y*y <= 4) && (iterations < MAX_ITERATIONS))
        {
            float xtemp = (x*x) - (y*y) + u_cx;
            y = 2.0*x*y + u_cy;
            x = xtemp;
            iterations++;
        }

        if (iterations == MAX_ITERATIONS) {
            return 0.0;
        }
        else {
            return iterations;
        }
    }
    
    void main()
    {
        float x = u_x0 + u_x * (gl_FragCoord.x / u_width);
        float y = u_y0 + u_y * (gl_FragCoord.y / u_width);

        float iterations;
        julia(x, y, iterations);
        float normalised = iterations / MAX_ITERATIONS;

        // FragColor = vec4(0.0, 0.0, 1.0, 0.0);
        FragColor = vec4(normalised, normalised, normalised, normalised);
    } 
)";
