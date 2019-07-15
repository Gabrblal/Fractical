#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/////////////////////////////////// Shader /////////////////////////////////////

Shader::Shader(const char *vertex, const char *fragment)
    : m_id(0)
{
    m_id = CreateProgram(vertex, fragment);
}

Shader::~Shader()
{
    // BUG: Creating temporary instances of Shader invokes the destructor that
    // deletes the program, making the new Shader object unusable.
    // See Shader::Destroy()

    // glDeleteProgram(m_id);
}

void Shader::Destroy()
{
    // Call this manually for destroying the shader, in the renderer.
    glDeleteProgram(m_id);
}

void Shader::Bind() const
{
    glUseProgram(m_id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

const char *Shader::ParseShader(const char *filepath)
{
    std::ifstream filestream(filepath);
    std::string line;
    std::string source;

    while (std::getline(filestream, line)) {
        std::cout << line;
        source.append(line).append("\n");
    }

    return source.c_str();
}

GLuint Shader::CreateProgram(const char *vertex, const char *fragment)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    int valid;
    int linked;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if ( (valid == GL_FALSE) || (linked == GL_FALSE)) {

        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];

        glGetProgramInfoLog(program, length, &length, message);
        std::cout << "Program failed: " << message << std::endl;

        delete[] message;
        return 0;

    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

GLuint Shader::CompileShader(const GLuint type, const char *source)
{
    // Create a new shader with reference id. glShaderSource replaces the
    // shaders source code with an array of strings, of which there are 1
    // and it is null terminated.
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    // glGetShaderiv returns an attribute from a shader object.
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];

        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Shader Compilation Error\n" << message << std::endl;

        delete[] message;

        return 0;
    }

    return id;
}

GLint Shader::GetUniformLocation(const char *name)
{
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end()) {
        return m_uniform_location_cache[name];
    }
    GLint location = glGetUniformLocation(m_id, name);
    if (location == -1) {
        std::cout << "Shader Warning: Uniform " << name << " does not exist." << std::endl;
    }
    
    m_uniform_location_cache[name] = location;
    std::cout << location << std::endl;
    return location;
}

void Shader::SetUniform1f(const char *name, GLfloat f1)
{
    glUniform1f(GetUniformLocation(name), f1);
}

void Shader::SetUniform4f(const char *name, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
    glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}

///////////////////////////////// Fractal //////////////////////////////////////

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

    uniform float u_x0;
    uniform float u_y0;
    uniform float u_x1;
    uniform float u_y1;

    float c = u_x0 + u_y0 + u_x1 + u_y1;
    
    void main()
    {
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    } 
)";

Fractal::Fractal(Settings &settings)
    : Shader(s_default_vert, s_default_frag)
    , m_settings(&settings)
{
    std::cout << "Binding and unbinding in Fractal Constructor" << std::endl;
    Bind();
    InitUniforms();
    Unbind();
}

void Fractal::InitUniforms() {
    SetUniform1f("u_x0", m_settings->window.x0);
    SetUniform1f("u_y0", m_settings->window.y0);
    SetUniform1f("u_x1", m_settings->window.x1);
    SetUniform1f("u_y1", m_settings->window.y1);
}

void Fractal::Update() {
    SetUniform1f("u_x0", m_settings->window.x0);
    SetUniform1f("u_y0", m_settings->window.y0);
    SetUniform1f("u_x1", m_settings->window.x1);
    SetUniform1f("u_y1", m_settings->window.y1);
    UpdateFractal();
}

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

    uniform float u_x0;
    uniform float u_y0;
    uniform float u_x1;
    uniform float u_y1;

    float mandelbrot(in float x0, in float y0, out int iterations)
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

        return iterations;
    
    }
    
    void main()
    {
        float x = u_x0 + (u_x1 - u_x0) * (gl_FragCoord.x / 1920); 
        float y = u_y0 + (u_y1 - u_y0) * (gl_FragCoord.y * 9 / 1080 / 16);

        int iterations;
        mandelbrot(x, y, iterations);
        float normalised = iterations / MAX_ITERATIONS;

        FragColor = vec4(normalised, normalised, normalised, normalised);
    } 
)";